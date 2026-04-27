#include "gps_l1_ca_double_chip_rate_tracking.h"
#include "GPS_L1_CA.h"
#include "configuration_interface.h"
#include "display.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>

#if USE_GLOG_AND_GFLAGS
#include <glog/logging.h>
#else
#include <absl/log/log.h>
#endif

GpsL1CaDoubleChipRateTracking::GpsL1CaDoubleChipRateTracking(
    const ConfigurationInterface* configuration,
    const std::string& role,
    unsigned int in_streams,
    unsigned int out_streams)
    : BaseDllPllTracking(configuration, role, in_streams, out_streams)
{
    configure_tracking_parameters(configuration);
    create_tracking_block();
}

// ¡Esta es la función a la que se le había roto el nombre!
void GpsL1CaDoubleChipRateTracking::configure_tracking_parameters(
    const ConfigurationInterface* configuration __attribute__((unused)))
{
    // Set basic signal identifiers
    config_params().system = 'G';
    const std::array<char, 3> sig{'1', 'C', '\0'};
    std::copy_n(sig.data(), 3, config_params().signal);

    // ====================================================================
    // 🚀 LA MAGIA DE TU LEO PNT (Sobrescribimos la física del Tracking)
    // ====================================================================
    config_params().chip_rate = 2046000.0;
    //config_params().code_length = 2046; 

    // Calculamos cuántas muestras hay en 1 milisegundo directamente
    const auto vector_length = static_cast<int>(std::round(config_params().fs_in / 1000.0));
    config_params().vector_length = vector_length;
    // ====================================================================

    // Sanity checks and warnings
    if (config_params().extend_correlation_symbols < 1)
        {
            config_params().extend_correlation_symbols = 1;
            std::cout << TEXT_RED
                      << "WARNING: GPS L1 C/A: extend_correlation_symbols must be > 0. "
                      << "Coherent integration set to 1 ms."
                      << TEXT_RESET << std::endl;
        }
    else if (config_params().extend_correlation_symbols > 20)
        {
            config_params().extend_correlation_symbols = 20;
            std::cout << TEXT_RED
                      << "WARNING: GPS L1 C/A: extend_correlation_symbols limited to 20 (20 ms)."
                      << TEXT_RESET << std::endl;
        }

    // GPS L1 C/A does not have a pilot component
    config_params().track_pilot = configuration->property(this->role() + ".track_pilot", false);
    if (config_params().track_pilot)
        {
            config_params().track_pilot = false;
            std::cout << TEXT_RED
                      << "WARNING: GPS L1 C/A does not have pilot signal. "
                      << "Data tracking enabled instead."
                      << TEXT_RESET << std::endl;
        }

    // Ensure bandwidth sanity when narrow-band is enabled
    if ((config_params().extend_correlation_symbols > 1) &&
        (config_params().pll_bw_narrow_hz > config_params().pll_bw_hz ||
            config_params().dll_bw_narrow_hz > config_params().dll_bw_hz))
        {
            std::cout << TEXT_RED
                      << "WARNING: GPS L1 C/A: Narrow tracking bandwidth is higher than wide bandwidth."
                      << TEXT_RESET << std::endl;
        }
}

void GpsL1CaDoubleChipRateTracking::create_tracking_block()
{
    // Create GNU Radio block
    if (config_params().item_type == "gr_complex")
        {
            tracking_sptr_ = dll_pll_veml_make_tracking(config_params());
            DLOG(INFO) << "Tracking block (" << tracking_sptr_->unique_id() << ")";
        }
    else
        {
            set_item_size(0);
            tracking_sptr_ = nullptr;
            LOG(WARNING) << config_params().item_type << " unknown tracking item type.";
        }
}
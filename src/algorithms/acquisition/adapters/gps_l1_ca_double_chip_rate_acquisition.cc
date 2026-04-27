/*!
 * \file gps_l1_ca_double_chip_rate_acquisition.cc
 * \brief Adapts a PCPS acquisition block for a custom Double Chip Rate GPS L1 C/A signal
 */

#include "gps_l1_ca_double_chip_rate_acquisition.h"
#include "GPS_L1_CA.h"
#include "gps_sdr_signal_replica.h"

// 1. El Constructor de la clase (Fijando la física a 2.046 Mcps)
GpsL1CaDoubleChipRateAcquisition::GpsL1CaDoubleChipRateAcquisition(
    const ConfigurationInterface* configuration,
    const std::string& role,
    unsigned int in_streams,
    unsigned int out_streams)
    : BasePcpsAcquisition(configuration,
          role,
          in_streams,
          out_streams,
          2046000.0,  // d_chip_rate
          8184000.0,  // d_opt_acq_fs_sps
          2046,       // d_code_length
          1.0)        // d_code_period_ms
{
}

// 2. El método de la clase (Que llama a la librería externa)
void GpsL1CaDoubleChipRateAcquisition::code_gen_complex_sampled(own::span<std::complex<float>> dest, uint32_t prn, int32_t sampling_freq)
{
    // Pasamos 0U en lugar de 0
    gps_l1_ca_double_chip_rate_code_gen_complex_sampled(dest, prn, sampling_freq, 0U);
}
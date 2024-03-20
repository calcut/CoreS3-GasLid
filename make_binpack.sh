# ~/git/Notecard-DFU/note-cli_1.2.1_macOS_arm64/notecard -binpack esp32 0x0:.pio/build/m5stack-cores3/bootloader.bin 0x8000:.pio/build/m5stack-cores3/partitions.bin 0x10000:.pio/build/m5stack-cores3/firmware.bin

# split -b 300K .pio/build/m5stack-cores3-gaslid/firmware.bin ./split_firmware_

# ~/git/Notecard-DFU/note-cli_1.2.1_macOS_arm64/notecard -binpack esp32 \
#   0x0:.pio/build/m5stack-cores3-gaslid/bootloader.bin \
#   0x8000:.pio/build/m5stack-cores3-gaslid/partitions.bin \
#   0x10000:split_firmware_aa \
#   0x5B000:split_firmware_ab \
#   0xA6000:split_firmware_ac \
#   0xF1000:split_firmware_ad 

  split -b 300K .pio/build/m5stack-cores3-septicsensor/firmware.bin ./split_firmware_

~/git/Notecard-DFU/note-cli_1.2.1_macOS_arm64/notecard -binpack esp32 \
  0x0:.pio/build/m5stack-cores3-septicsensor/bootloader.bin \
  0x8000:.pio/build/m5stack-cores3-septicsensor/partitions.bin \
  0x10000:split_firmware_aa \
  0x5B000:split_firmware_ab \
  0xA6000:split_firmware_ac \
  0xF1000:split_firmware_ad 
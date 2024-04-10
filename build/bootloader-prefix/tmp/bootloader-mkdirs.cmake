# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/dev/Espressif/frameworks/esp-idf-v5.0.1/components/bootloader/subproject"
  "C:/dev/ESP32_workspace/SPI_LCD_ST7789/build/bootloader"
  "C:/dev/ESP32_workspace/SPI_LCD_ST7789/build/bootloader-prefix"
  "C:/dev/ESP32_workspace/SPI_LCD_ST7789/build/bootloader-prefix/tmp"
  "C:/dev/ESP32_workspace/SPI_LCD_ST7789/build/bootloader-prefix/src/bootloader-stamp"
  "C:/dev/ESP32_workspace/SPI_LCD_ST7789/build/bootloader-prefix/src"
  "C:/dev/ESP32_workspace/SPI_LCD_ST7789/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/dev/ESP32_workspace/SPI_LCD_ST7789/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/dev/ESP32_workspace/SPI_LCD_ST7789/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()

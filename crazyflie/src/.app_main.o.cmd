cmd_/home/z/projects/code/crazyflie/src/app_main.o := arm-none-eabi-gcc -Wp,-MD,/home/z/projects/code/crazyflie/src/.app_main.o.d     -I/home/z/projects/code/crazyflie/src -D__firmware__ -fno-exceptions -Wall -Wmissing-braces -fno-strict-aliasing -ffunction-sections -fdata-sections -Wdouble-promotion -std=gnu11 -DCRAZYFLIE_FW   -I/home/z/projects/crazyflie/crazyflie-firmware/vendor/CMSIS/CMSIS/Core/Include   -I/home/z/projects/crazyflie/crazyflie-firmware/vendor/CMSIS/CMSIS/DSP/Include   -I/home/z/projects/crazyflie/crazyflie-firmware/vendor/libdw1000/inc   -I/home/z/projects/crazyflie/crazyflie-firmware/vendor/FreeRTOS/include   -I/home/z/projects/crazyflie/crazyflie-firmware/vendor/FreeRTOS/portable/GCC/ARM_CM4F   -I/home/z/projects/crazyflie/crazyflie-firmware/src/config   -I/home/z/projects/crazyflie/crazyflie-firmware/src/platform/interface   -I/home/z/projects/crazyflie/crazyflie-firmware/src/deck/interface   -I/home/z/projects/crazyflie/crazyflie-firmware/src/deck/drivers/interface   -I/home/z/projects/crazyflie/crazyflie-firmware/src/drivers/interface   -I/home/z/projects/crazyflie/crazyflie-firmware/src/drivers/bosch/interface   -I/home/z/projects/crazyflie/crazyflie-firmware/src/drivers/esp32/interface   -I/home/z/projects/crazyflie/crazyflie-firmware/src/hal/interface   -I/home/z/projects/crazyflie/crazyflie-firmware/src/modules/interface   -I/home/z/projects/crazyflie/crazyflie-firmware/src/modules/interface/kalman_core   -I/home/z/projects/crazyflie/crazyflie-firmware/src/modules/interface/lighthouse   -I/home/z/projects/crazyflie/crazyflie-firmware/src/modules/interface/cpx   -I/home/z/projects/crazyflie/crazyflie-firmware/src/modules/interface/p2pDTR   -I/home/z/projects/crazyflie/crazyflie-firmware/src/utils/interface   -I/home/z/projects/crazyflie/crazyflie-firmware/src/utils/interface/kve   -I/home/z/projects/crazyflie/crazyflie-firmware/src/utils/interface/lighthouse   -I/home/z/projects/crazyflie/crazyflie-firmware/src/utils/interface/tdoa   -I/home/z/projects/crazyflie/crazyflie-firmware/src/lib/FatFS   -I/home/z/projects/crazyflie/crazyflie-firmware/src/lib/CMSIS/STM32F4xx/Include   -I/home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32_USB_Device_Library/Core/inc   -I/home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32_USB_OTG_Driver/inc   -I/home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc   -I/home/z/projects/crazyflie/crazyflie-firmware/src/lib/vl53l1   -I/home/z/projects/crazyflie/crazyflie-firmware/src/lib/vl53l1/core/inc   -I/home/z/projects/code/crazyflie/build/include/generated -fno-delete-null-pointer-checks --param=allow-store-data-races=0 -Wno-unused-but-set-variable -Wno-unused-const-variable -fomit-frame-pointer -fno-var-tracking-assignments -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=date-time -DCC_HAVE_ASM_GOTO -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g3 -fno-math-errno -DARM_MATH_CM4 -D__FPU_PRESENT=1 -mfp16-format=ieee -Wno-array-bounds -Wno-stringop-overread -Wno-stringop-overflow -DSTM32F4XX -DSTM32F40_41xxx -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER -Os -Werror   -c -o /home/z/projects/code/crazyflie/src/app_main.o /home/z/projects/code/crazyflie/src/app_main.c

source_/home/z/projects/code/crazyflie/src/app_main.o := /home/z/projects/code/crazyflie/src/app_main.c

deps_/home/z/projects/code/crazyflie/src/app_main.o := \
  /usr/include/newlib/string.h \
  /usr/include/newlib/_ansi.h \
  /usr/include/newlib/newlib.h \
  /usr/include/newlib/_newlib_version.h \
  /usr/include/newlib/sys/config.h \
    $(wildcard include/config/h//.h) \
  /usr/include/newlib/machine/ieeefp.h \
  /usr/include/newlib/sys/features.h \
  /usr/include/newlib/sys/reent.h \
  /usr/include/newlib/_ansi.h \
  /usr/lib/gcc/arm-none-eabi/9.2.1/include/stddef.h \
  /usr/include/newlib/sys/_types.h \
  /usr/include/newlib/machine/_types.h \
  /usr/include/newlib/machine/_default_types.h \
  /usr/include/newlib/sys/lock.h \
  /usr/include/newlib/sys/cdefs.h \
  /usr/include/newlib/sys/_locale.h \
  /usr/include/newlib/strings.h \
  /usr/include/newlib/sys/string.h \
  /usr/lib/gcc/arm-none-eabi/9.2.1/include/stdint.h \
  /usr/lib/gcc/arm-none-eabi/9.2.1/include/stdbool.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/modules/interface/app.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/FreeRTOS/include/FreeRTOS.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/config/FreeRTOSConfig.h \
    $(wildcard include/config/h.h) \
    $(wildcard include/config/debug/queue/monitor.h) \
  /home/z/projects/crazyflie/crazyflie-firmware/src/config/config.h \
    $(wildcard include/config/h/.h) \
    $(wildcard include/config/block/address.h) \
  /home/z/projects/crazyflie/crazyflie-firmware/src/drivers/interface/nrf24l01.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/drivers/interface/nRF24L01reg.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/config/trace.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/hal/interface/usec_time.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/utils/interface/cfassert.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/config/stm32fxxx.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/CMSIS/STM32F4xx/Include/stm32f4xx.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/CMSIS/CMSIS/Core/Include/core_cm4.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/CMSIS/CMSIS/Core/Include/cmsis_version.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/CMSIS/CMSIS/Core/Include/cmsis_compiler.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/CMSIS/CMSIS/Core/Include/cmsis_gcc.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/CMSIS/CMSIS/Core/Include/mpu_armv7.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/CMSIS/STM32F4xx/Include/system_stm32f4xx.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/config/stm32f4xx_conf.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_adc.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_crc.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dbgmcu.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dma.h \
    $(wildcard include/config/it.h) \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_exti.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_flash.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_gpio.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_i2c.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_iwdg.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_pwr.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rcc.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rtc.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_sdio.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_spi.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_syscfg.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_tim.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_usart.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_wwdg.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_misc.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_cryp.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_hash.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_rng.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_can.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dac.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_dcmi.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/lib/STM32F4xx_StdPeriph_Driver/inc/stm32f4xx_fsmc.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/modules/interface/console.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/utils/interface/eprintf.h \
  /usr/lib/gcc/arm-none-eabi/9.2.1/include/stdarg.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/FreeRTOS/include/projdefs.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/FreeRTOS/include/portable.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/FreeRTOS/include/deprecated_definitions.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/FreeRTOS/portable/GCC/ARM_CM4F/portmacro.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/FreeRTOS/include/mpu_wrappers.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/FreeRTOS/include/task.h \
  /home/z/projects/crazyflie/crazyflie-firmware/vendor/FreeRTOS/include/list.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/utils/interface/debug.h \
    $(wildcard include/config/debug/print/on/uart1.h) \
  /home/z/projects/crazyflie/crazyflie-firmware/src/config/config.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/drivers/interface/uart1.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/modules/interface/crtp_commander_high_level.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/modules/interface/math3d.h \
  /usr/include/newlib/math.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/modules/interface/stabilizer_types.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/hal/interface/imu_types.h \
  /home/z/projects/crazyflie/crazyflie-firmware/src/utils/interface/lighthouse/lighthouse_types.h \

/home/z/projects/code/crazyflie/src/app_main.o: $(deps_/home/z/projects/code/crazyflie/src/app_main.o)

$(deps_/home/z/projects/code/crazyflie/src/app_main.o):

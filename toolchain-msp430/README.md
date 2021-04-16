# MSP430 Toolchain

To update the docker image follow the next steps:

1) Modify `MSP430_toolchain.Dockerfile`. 
    - The following lines are related to the texas instrument toolchain:

```sh
RUN wget https://software-dl.ti.com/codegen/esd/cgt_public_sw/MSP430/20.2.2.LTS/ti_cgt_msp430_20.2.2.LTS_linux_installer_x86.bin && ls -la && pwd

RUN chmod +x ./ti_cgt_msp430_20.2.2.LTS_linux_installer_x86.bin 
RUN echo | /home/dev/ti_cgt_msp430_20.2.2.LTS_linux_installer_x86.bin --prefix /usr/toolchain/
```

2) Update the `ccs_base` folder with newer libraries from Texas Instrument.
    - Download Code Composer Studio
    - `ccs_base` is under `<INSTALLATION_DIR>/ccs1000/ccs/`

3) Add the correct `IMAGE_NAME` in the `UpdateDockerImageOnGitlab.sh` 

4) Run `UpdateDockerImageOnGitlab.sh` 

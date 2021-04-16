# DIALOG 1468X Toolchain

To update the docker image follow the next steps:

1) Update the following folders `boards/` and `GCC/`

```sh
├── boards
│   ├── DA14681
│   ├── DA14683
│   └── sdk
├── GCC
```
    - To update `GCC`:
        - Download `Smart Snippets Studio`
        - Copy `GCC` from `<INSTALLATION_DIR>/SmartSnippetsStudio<VER>/`

    - To update `boards`:
        - Download Dialog SDK.
        - Copy `sdk` from `<INSTALLATION_DIR>/DA1468x_DA15xxx_SDK_<VER>/`
        - Copy to `DA14681` the following files:
            - `<INSTALLATION_DIR>/DA1468x_DA15xxx_SDK_<VER>/sdk/interfaces/ble_stack/DA14681-01-dbg-Debug/libble_stack_da14681_01_dbg.a`
            - `<INSTALLATION_DIR>/DA1468x_DA15xxx_SDK_<VER>/sdk/interfaces/ble_stack/DA14681-01-Debug/libble_stack_da14681_01.a`

        - Copy to `DA14683` the following files:
            - `<INSTALLATION_DIR>/DA1468x_DA15xxx_SDK_<VER>/sdk/interfaces/ble_stack/DA14683-00-Debug/libble_stack_da14683_00.a`
            - `<INSTALLATION_DIR>/DA1468x_DA15xxx_SDK_<VER>/sdk/interfaces/ble_stack/DA14683-00-dbg-Debug/libble_stack_da14683_00_dbg.a`

2) Modify `Dockerfile` if necessary.

3) Create a new Tag to let the GitLab build the new docker

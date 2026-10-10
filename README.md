# Myst IV: Revelation — Resolution Fix

A modified version of **Racer_S's Universal Resolution Changer**, adapted to improve resolution compatibility with **Myst IV: Revelation** on modern Windows systems.

This project provides the modified C++ source code and a precompiled `d3d9.dll` for players who want to run Myst IV at higher resolutions without having to build the fix themselves.

## Features

- Support for custom display resolutions.
- Improvements to resolution handling for Myst IV: Revelation.
- Compatibility adjustments for modern displays.
- Precompiled DLL for easy installation.
- Source code available for inspection and further modification.

## Installation

1. Download the latest release from this repository.
2. Extract the provided files.
3. Place `d3d9.dll` and any accompanying configuration files in the Myst IV game directory, alongside the game's executable.
4. Configure the desired resolution if required.
5. Launch the game.

**Important:** Back up any existing `d3d9.dll` before replacing it. This fix may conflict with other tools that use the same DLL.

## Tested Configuration

This modification was developed and tested with:

- **Game:** Myst IV: Revelation
- **Operating system:** Windows
- **Resolution:** 1824 × 1368

Compatibility with other resolutions, game distributions and system configurations is not guaranteed.

### Resolution Configuration

The resolution **1824 × 1368** used in my configuration is intentional. It accounts for the space occupied by my Windows taskbar, allowing the game to fit within the available desktop area without overlapping it.

This is a personal configuration choice, not a technical limitation of the fix.

You can adjust the resolution values to match your own monitor, taskbar layout, and preferred display configuration.

## Building from Source

The modified C++ source code is included in this repository for developers who prefer to compile the DLL themselves.

The project is intended for Windows and uses the Direct3D 9 proxy DLL approach.

## Credits

**Original project:** Universal Resolution Changer  
**Original author:** Racer_S

Original download and project information:

https://community.pcgamingwiki.com/files/file/509-universal-resolution-changer/

This repository contains modifications made specifically to improve the experience of playing Myst IV: Revelation.

Full credit for the original Universal Resolution Changer belongs to Racer_S.

## Disclaimer

This is an unofficial, community-maintained modification.

It is not affiliated with or endorsed by Cyan Worlds, Ubisoft, or the original author of Universal Resolution Changer.

The software is provided as-is, without warranty. Use it at your own risk.

Myst and Myst IV: Revelation are trademarks of their respective owners.

## License

The licensing and redistribution terms of the original Universal Resolution Changer must be verified before assigning a license to this modified version.

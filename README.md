# Amiga-Stuff: Native & Cross-Dev Code & Tools for Amigas


## SysTest Binaries

The latest build of SysTest can always be found [here (Google Drive)]
(https://drive.google.com/open?id=0B6F45EdkSMp1ZGhXMWRvOXVDd3M).


## Summary

This is a selection of code that I will add to over time. There are
three main file types, distinguished by suffix:
- **.S**    CPP + GAS assembler syntax (for cross-dev environments)
- **.asm**  Amiga native asm syntax (Devpac, AsmOne, PhxAss, vasm, Barfly, ...)
- **.c**    Somewhat-portable C (I will gladly take patches to make the C code
            work outside a GCC/POSIX environment).

All code is public domain (see the COPYING file).


## File Descriptions

For detailed build and usage instructions, see
file header comments and run-time help info.

- **base/**
  GNU build rules, initialisation code, utility code and headers.

- **systest/**
  Amiga system tests, built as a Workbench/CLI executable and as a
  bootable disk image.

- **kickconv**
  Convert Kickstart ROM images: byte-swap, word-split, decrypt, fix checksums.
  Especially useful for creating images for burning to EPROM.

- **crc16_ccitt.S**
  Table-driven CRC16-CCITT implementation.

- **degzip_{gnu,portable}.c**
  Analyse gzip files, extract and write out their raw Deflate streams
  (can then be processed by inflate, see below).
  Original version for GNU/Linux, and portable version fixed by phx / EAB.

- **inflate.{S,asm}**
  Small and efficient implementation of Inflate, as specified
  in RFC 1951 "DEFLATE Compressed Data Format Specification".

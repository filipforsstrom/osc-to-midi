# flake.nix
{
  description = "test";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
    ...
  } @ inputs: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
    juce-src = pkgs.fetchFromGitHub {
      "owner" = "juce-framework";
      "repo" = "JUCE";
      "rev" = "5179f4e720d8406ebd1b5401c86aea8da6cc83c9";
      "hash" = "sha256-faD1iI9cQ2v3YisbMDtk2lRELR7eDTz3JP0K0p1vmEU=";
      "fetchSubmodules" = true;
    };
  in {
    devShells.x86_64-linux.default =
      pkgs.mkShell
      {
        nativeBuildInputs = with pkgs; [
          clang
          gdb
          cmake
          ninja
          # juce dependencies
          pkg-config
          alsaLib
          libjack2
          ladspa-sdk
          curl
          freetype
          fontconfig
          xorg.libX11
          xorg.libXcomposite
          xorg.libXcursor
          xorg.libXext
          xorg.libXinerama
          xorg.libXrandr
          xorg.libXrender
          webkitgtk
          libGLU
          # can these be changed?
          pcre2
          util-linux
          libselinux
          libsepol
          libthai
          libdatrie
          xorg.libXdmcp
          lerc
          libxkbcommon
          libepoxy
          xorg.libXtst
          libsysprof-capture
          sqlite
          # Add python with oscpy package
          (python312.withPackages (ps: [ps.oscpy]))
          liblo # monitor osc
        ];
        JUCE_SRC = juce-src;
      };
  };
}

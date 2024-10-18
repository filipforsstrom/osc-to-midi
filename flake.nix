# flake.nix

{
  description = "test";

  inputs =
    {
      nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    };

  outputs = { self, nixpkgs, ... }@inputs:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      juce-src = pkgs.fetchFromGitHub {
        "owner" = "juce-framework";
        "repo" = "JUCE";
        "rev" = "5179f4e720d8406ebd1b5401c86aea8da6cc83c9";
        "hash" = "sha256-faD1iI9cQ2v3YisbMDtk2lRELR7eDTz3JP0K0p1vmEU=";
      };
    in
    {
      devShells.x86_64-linux.default =
        pkgs.mkShell
          {
            nativeBuildInputs = with pkgs; [
              cmake
            ];
          };
    };
}

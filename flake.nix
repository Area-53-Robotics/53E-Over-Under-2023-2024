{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
    pros-cli-nix.url = "github:BattleCh1cken/pros-cli-nix";
  };

  outputs =
    { self
    , nixpkgs
    , utils
    , pros-cli-nix
    }:
    utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs { inherit system; };
    in
    {
      devShell = pkgs.mkShell {
        packages = with pkgs; [
          pros-cli-nix.packages.${system}.default
          clang-tools
          gcc-arm-embedded-10

          # Python deps for graphing
          nodePackages_latest.pyright
          black

          python310Packages.matplotlib
          python310Packages.numpy
          python310Packages.pandas
          python310Packages.bleak
          python310Packages.paho-mqtt
          python310
        ];
      };
    });
}

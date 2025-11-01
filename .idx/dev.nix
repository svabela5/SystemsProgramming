{ pkgs, ... }: {
  channel = "stable-24.05";
  packages = [
    pkgs.gcc
  ];
  idx = {
    previews = {
      enable = false;
    };
  };
}

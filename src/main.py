from src.install.InstallServiceDiscovery import InstallServiceDiscovery
from src.installer_ui import InstallerUI
from src.utils.os.OSResolver import OSResolver

if __name__ == '__main__':
    ui = InstallerUI(InstallServiceDiscovery(OSResolver.resolve()))
    ui.draw()

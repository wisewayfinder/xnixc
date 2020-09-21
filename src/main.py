from typing import Set, List, Dict

from src.install.InstallServiceDiscovery import InstallServiceDiscovery
from src.install.PkgCatalog import PkgCatalog
from src.install.SuggestInstallCandidatePkgService import SuggestInstallCandidatePkgService
from src.install.installer.PkgInstaller import PkgInstaller
from src.installer_ui import InstallerUI
from src.utils.os.OSResolver import OSResolver

if __name__ == '__main__':
    install_service_discovery = InstallServiceDiscovery(OSResolver.resolve())

    install_candidates: Set[PkgCatalog] = SuggestInstallCandidatePkgService.suggest(
        install_service_discovery.pkg_dependency_dag_provider(),
        install_service_discovery.pkg_install_check_service()
    )
    installer_list: List[PkgInstaller] = list(
        map(lambda it: install_service_discovery.installer_resolver().execute(it),
            install_candidates))
    installer_dict: Dict[int, PkgInstaller] = {}
    for idx in range(0, len(installer_list)):
        installer_dict[idx + 1] = installer_list[idx]

    ui = InstallerUI(installer_dict)
    InstallerUI.draw(ui)

from typing import Dict, Set, List

from src.install.InstallServiceDiscovery import InstallServiceDiscovery
from src.install.PkgCatalog import PkgCatalog
from src.install.SuggestInstallCandidatePkgService import SuggestInstallCandidatePkgService
from src.install.installer.PkgInstaller import PkgInstaller
from src.install.installer.ExitInstaller import ExitInstaller
from src.install.installer.SudoInstaller import SudoInstaller


class InstallerUI:
    __sudo_cmd_code = 0
    __exit_cmd_code = -1
    __sudo_installer = SudoInstaller()

    def __init__(self, install_service_discovery: InstallServiceDiscovery):
        self.__install_service_discovery = install_service_discovery
        self.__install_dict: Dict[int, PkgInstaller] = {}
        super().__init__()

    def draw(self):
        while True:
            self.__refresh_install_dict()
            self.__print_ui()
            try:
                cmd = InstallerUI.__input_cmd()
                self.__check_cmd_valid(cmd)
            except (TypeError, KeyError) as e:
                print("\n")
                print(e)
                print("\n")
                continue
            self.__run_command(cmd)

    def __refresh_install_dict(self):
        install_candidates: Set[PkgCatalog] = SuggestInstallCandidatePkgService.suggest(
            self.__install_service_discovery.pkg_dependency_dag_provider(),
            self.__install_service_discovery.pkg_install_check_service()
        )
        installer_list: List[PkgInstaller] = sorted(
            list(
                map(
                    lambda it: self.__install_service_discovery.installer_resolver(self.__sudo_installer.get_pw()).execute(it),
                    install_candidates)),
            key=lambda it: it.one_line_description())
        installer_dict: Dict[int, PkgInstaller] = {
            self.__sudo_cmd_code: self.__sudo_installer,
            self.__exit_cmd_code: ExitInstaller()
        }
        for idx in range(0, len(installer_list)):
            installer_dict[idx + 1] = installer_list[idx]
        self.__install_dict = installer_dict

    @staticmethod
    def __input_cmd() -> int:
        cmd_str = input()
        try:
            return int(cmd_str)
        except ValueError:
            raise TypeError(f"cmd should be number but not, '{cmd_str}'")

    def __print_ui(self):
        print('********        xnixc installer        ********\n')
        for cmd in sorted(list(filter(lambda it: it > 0, self.__install_dict.keys()))):
            print('[{:-3} ] {}'.format(
                cmd,
                self.__install_dict[cmd].one_line_description()))
        print('')
        for cmd in sorted(list(filter(lambda it: it <= 0, self.__install_dict.keys())), reverse=True):
            print('[{:-3} ] {}'.format(
                cmd,
                self.__install_dict[cmd].one_line_description()))

        print('\nselect number to install >> ', end='')

    def __check_cmd_valid(self, cmd):
        if cmd not in self.__install_dict.keys():
            raise KeyError(f"command {cmd} is not exist in list")

    def __run_command(self, cmd: int):
        installer = self.__install_dict[cmd]
        installer.install()

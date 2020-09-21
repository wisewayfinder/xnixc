from typing import Dict
from src.install.installer.PkgInstaller import PkgInstaller
from src.install.installer.ExitInstaller import ExitInstaller


class InstallerUI:
    __exit_cmd_code = -1
    __exist_installer = ExitInstaller()

    def __init__(self, cmd_installer_map: Dict[int, PkgInstaller]):
        self.__cmd_installer_map = cmd_installer_map
        super().__init__()

    @staticmethod
    def __input_cmd() -> int:
        cmd_str = input()
        try:
            return int(cmd_str)
        except ValueError:
            raise TypeError(f"cmd should be number but not, '{cmd_str}'")

    def draw(self):
        while True:
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

    def __print_ui(self):
        print('********        xnixc installer        ********\n')
        for cmd in sorted(list(filter(lambda it: it > 0, self.__cmd_installer_map.keys()))):
            print('[{:-3} ] {}'.format(
                cmd,
                self.__cmd_installer_map[cmd].one_line_description()))

        print('[{:-3} ] {}'.format(
            self.__exit_cmd_code,
            ExitInstaller().one_line_description()))
            
        print('\nselect number to install >> ', end='')

    def __check_cmd_valid(self, cmd):
        if cmd == self.__exit_cmd_code:
            return
        if cmd not in self.__cmd_installer_map.keys():
            raise KeyError(f"command {cmd} is not exist in list")

    def __run_command(self, cmd: int):
        if cmd == self.__exit_cmd_code:
            self.__exist_installer.install()
        else:
            installer = self.__cmd_installer_map[cmd]
            installer.install()

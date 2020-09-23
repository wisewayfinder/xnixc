from getpass import getpass
from src.install.installer.PkgInstaller import PkgInstaller


class SudoInstaller(PkgInstaller):
    def __init__(self) -> None:
        self.__is_set: bool = False
        self.__password: str = ''
        super().__init__()

    def one_line_description(self) -> str:
        return "Caching 'su' password to made other task automatically"

    def install(self) -> None:
        if not self.__is_set:
            self.__password = getpass()
            self.__is_set = True
        else:
            print('It looks password already set, do you want change? [y]: ',
                  end='')
            want_change = input().lower()
            if want_change == 'y' or want_change == '':
                self.__password = getpass()
            else:
                print('Keep caching password')

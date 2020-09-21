import os
import subprocess
from typing import Dict, Callable

from src.install.PkgCatalog import PkgCatalog
from src.install.check.PkgInstallCheckService import PkgInstallCheckService


class Ubuntu2004PkgInstallCheckService(PkgInstallCheckService):
    def _define_behavior(self) -> Dict[PkgCatalog, Callable[[None], bool]]:
        return {
            PkgCatalog.CLANG: lambda _: subprocess.run(['which', 'clang-10'], capture_output=True).returncode == 0,
            PkgCatalog.VIM: lambda _: subprocess.run(['which', 'vim'], capture_output=True).returncode == 0,
            PkgCatalog.GIT: lambda _: subprocess.run(['which', 'git'], capture_output=True).returncode == 0,
            PkgCatalog.CTAGS: lambda _: subprocess.run(['which', 'ctags'], capture_output=True).returncode == 0,
            PkgCatalog.CMAKE: lambda _: subprocess.run(['which', 'cmake'], capture_output=True).returncode == 0,
            PkgCatalog.VUNDLE: lambda _: os.system('(ls ~/.vim/bundle | grep Vundle.vim) >/dev/null 2>&1') == 0,
            PkgCatalog.YCM: lambda _: os.system('(ls ~/.vim/bundle | grep YouCompleteMe) >/dev/null 2>&1') == 0,
            PkgCatalog.NERD_TREE: lambda _: os.system('(ls ~/.vim/bundle | grep nerdtree) >/dev/null 2>&1') == 0,
            PkgCatalog.CSCOPE: lambda _: subprocess.run(['which', 'cscope'], capture_output=True).returncode == 0,
            PkgCatalog.TAG_LIST: lambda _: os.system('(ls ~/.vim/bundle | grep taglist.vim) >/dev/null 2>&1') == 0,
            PkgCatalog.EASY_TAG: lambda _: os.system('(ls ~/.vim/bundle | grep vim-easytags) >/dev/null 2>&1') == 0,
            PkgCatalog.VIM_AIRLINE: lambda _: os.system('(ls ~/.vim/bundle | grep vim-airline) >/dev/null 2>&1') == 0,
            PkgCatalog.XNIXC: lambda _: os.system('(ls ~/.xnixc | grep .xnixc) >/dev/null 2>&1') == 0
        }

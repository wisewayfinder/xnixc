from abc import abstractmethod, ABC


class PkgInstaller(ABC):
    @abstractmethod
    def one_line_description(self) -> str:
        raise NotImplementedError

    @abstractmethod
    def install(self) -> None:
        raise NotImplementedError

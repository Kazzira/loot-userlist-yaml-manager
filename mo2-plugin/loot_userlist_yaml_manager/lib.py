"""
Loot User List YAML Manager Library Interface

This module provides an interface to the Loot User List YAML Manager library.
It allows for the creation and management of handles to the library,
as well as the retrieval of return codes and error messages.

:author: Zachary D Meyer
"""

import pathlib
import sys
from ctypes import c_char_p, c_uint32, c_void_p, POINTER, byref, CDLL
from typing import Protocol
from dataclasses import dataclass


class _Lib:
    """
    A singleton class that provides access to the Loot User List YAML Manager library.
    """

    @dataclass(frozen=True)
    class ReturnCodes:
        """
        Return codes for the Loot User List YAML Manager library.

        # Attributes:
        - ok: int - Indicates a successful operation.
        - err_allocation_failed: int - Indicates a memory allocation failure.
        - err_load_order_file_not_found: int - Indicates that the load order file was not found.
        - err_load_order_file_invalid: int - Indicates that the load order file is invalid.
        - err_config_json_file_not_found: int - Indicates that the configuration JSON file was not found.
        - err_config_json_file_invalid: int - Indicates that the configuration JSON file is invalid.
        - err_userlist_error_json_included: int - Error with JSON text.
        """

        ok: int
        err_allocation_failed: int
        err_load_order_file_not_found: int
        err_load_order_file_invalid: int
        err_config_json_file_not_found: int
        err_config_json_file_invalid: int
        err_userlist_error_json_included: int

    __instance: "_Lib"

    @staticmethod
    def instance() -> "_Lib":
        """
        Get the singleton instance of the _Lib class.

        :return: The singleton instance of _Lib.
        :rtype: _Lib
        """
        if not hasattr(_Lib, "__instance"):
            _Lib.__instance = _Lib()
        return _Lib.__instance

    def __init__(self) -> None:
        if sys.platform.startswith("win"):
            self.__lib = CDLL(
                str(pathlib.Path(__file__).parent / "LootUserListYAMLManagerFFI.dll")
            )
        else:
            self.__lib = CDLL(
                str(pathlib.Path(__file__).parent / "libLootUserListYAMLManagerFFI.so")
            )
        self.__lib.LUYAMLMAN_OK.argtypes = []
        self.__lib.LUYAMLMAN_OK.restype = c_uint32

        self.__lib.LUYAMLMAN_ERR_ALLOCATION_FAILED.argtypes = []
        self.__lib.LUYAMLMAN_ERR_ALLOCATION_FAILED.restype = c_uint32

        self.__lib.LUYAMLMAN_ERR_LOAD_ORDER_FILE_NOT_FOUND.argtypes = []
        self.__lib.LUYAMLMAN_ERR_LOAD_ORDER_FILE_NOT_FOUND.restype = c_uint32

        self.__lib.LUYAMLMAN_ERR_LOAD_ORDER_FILE_INVALID.argtypes = []
        self.__lib.LUYAMLMAN_ERR_LOAD_ORDER_FILE_INVALID.restype = c_uint32

        self.__lib.LUYAMLMAN_ERR_CONFIG_JSON_FILE_NOT_FOUND.argtypes = []
        self.__lib.LUYAMLMAN_ERR_CONFIG_JSON_FILE_NOT_FOUND.restype = c_uint32

        self.__lib.LUYAMLMAN_ERR_CONFIG_JSON_FILE_INVALID.argtypes = []
        self.__lib.LUYAMLMAN_ERR_CONFIG_JSON_FILE_INVALID.restype = c_uint32

        self.__lib.LUYAMLMAN_ERR_USERLIST_ERROR_JSON_INCLUDED.argtypes = []
        self.__lib.LUYAMLMAN_ERR_USERLIST_ERROR_JSON_INCLUDED.restype = c_uint32

        self.__lib.loot_userlist_yaml_manager_create_handle.argtypes = [
            POINTER(c_void_p),
            c_char_p,
            c_char_p,
            POINTER(c_char_p),
        ]
        self.__lib.loot_userlist_yaml_manager_create_handle.restype = c_uint32

        self.__lib.loot_userlist_yaml_manager_destroy_handle.argtypes = [c_void_p]
        self.__lib.loot_userlist_yaml_manager_destroy_handle.restype = None

        self.__lib.loot_userlist_yaml_manager_destroy_string.argtypes = [c_char_p]
        self.__lib.loot_userlist_yaml_manager_destroy_string.restype = None

        self.__return_codes = self.ReturnCodes(
            ok=self.__lib.LUYAMLMAN_OK(),
            err_allocation_failed=self.__lib.LUYAMLMAN_ERR_ALLOCATION_FAILED(),
            err_load_order_file_not_found=self.__lib.LUYAMLMAN_ERR_LOAD_ORDER_FILE_NOT_FOUND(),
            err_load_order_file_invalid=self.__lib.LUYAMLMAN_ERR_LOAD_ORDER_FILE_INVALID(),
            err_config_json_file_not_found=self.__lib.LUYAMLMAN_ERR_CONFIG_JSON_FILE_NOT_FOUND(),
            err_config_json_file_invalid=self.__lib.LUYAMLMAN_ERR_CONFIG_JSON_FILE_INVALID(),
            err_userlist_error_json_included=self.__lib.LUYAMLMAN_ERR_USERLIST_ERROR_JSON_INCLUDED(),
        )

    @property
    def return_codes(self) -> ReturnCodes:
        """
        Get the return codes for the Loot User List YAML Manager library.
        :return: An instance of ReturnCodes containing the return codes.
        """
        return self.__return_codes

    def create_handle(
        self, load_order_path: str, config_json_path: str, handle: c_void_p
    ) -> tuple[int, c_char_p]:
        """
        Create a handle for the Loot User List YAML Manager.

        :param load_order_path: The path to the load order file.
        :type load_order_path: str
        :param config_json_path: The path to the configuration JSON file.
        :type config_json_path: str
        :param handle: A pointer to a c_void_p where the handle will be stored.
        :type handle: c_void_p

        :return: A tuple containing the result code and an error message if applicable.
        """
        error_message = c_char_p()
        return (
            self.__lib.loot_userlist_yaml_manager_create_handle(
                byref(handle),
                load_order_path.encode("utf-8"),
                config_json_path.encode("utf-8"),
                byref(error_message),
            ),
            error_message,
        )

    def destroy_handle(self, handle: c_void_p) -> None:
        """
        Destroy the handle for the Loot User List YAML Manager.

        :param handle: The handle to be destroyed.
        :type handle: c_void_p
        """
        self.__lib.loot_userlist_yaml_manager_destroy_handle(handle)

    def destroy_string(self, string: c_char_p) -> None:
        """
        Destroy a string allocated by the Loot User List YAML Manager.

        :param string: The string to be destroyed.
        :type string: c_char_p
        """
        self.__lib.loot_userlist_yaml_manager_destroy_string(string)


class IManagerInUseContext(Protocol):
    """
    The LOOT User List YAML Manager context created by the ManagerHandle.
    """

    def __bool__(self) -> bool: ...


class IManager(Protocol):
    """
    The LOOT User List YAML Manager interface.
    This interface only defines the context manager methods for creating and managing a handle.
    """

    def __enter__(self) -> IManagerInUseContext:
        """
        Enter the context manager and return the context object.
        """

    def __exit__(self, exc_type, exc_value, traceback):
        """
        Exit the context manager and clean up the handle.
        """


class ManagerHandle:
    """
    A context manager for creating and managing a handle to the Loot User List YAML Manager.
    """

    @staticmethod
    def create(load_order_path: str, config_json_path: str) -> IManager:
        """
        Create a new ManagerHandle instance.

        :param load_order_path: The path to the load order file.
        :type load_order_path: str
        :param config_json_path: The path to the configuration JSON file.
        :type config_json_path: str

        :return: An instance of ManagerHandle.
        """
        return ManagerHandle(load_order_path, config_json_path)

    def __init__(self, load_order_path: str, config_json_path: str) -> None:
        self.__load_order_path = load_order_path
        self.__config_json_path = config_json_path
        self.__handle = c_void_p(0)
        self.__char_ptr = c_char_p(0)

    def __bool__(self) -> bool:
        return self.__handle.value is not None

    def __enter__(self) -> IManagerInUseContext:
        result, error_message = _Lib.instance().create_handle(
            self.__load_order_path, self.__config_json_path, self.__handle
        )

        # Will want to throw an exception if the result is not OK.
        # Currently, do not have json support in the DLL so not error text.

        return self

    def __exit__(self, exc_type, exc_value, traceback):
        if self.__handle:
            _Lib.instance().destroy_handle(self.__handle)
            self.__handle = c_void_p(0)

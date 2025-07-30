from pathlib import Path
from loot_userlist_yaml_manager.lib import ManagerHandle


def test_create_handle_error_occurs():
    with ManagerHandle("invalid_path", "invalid_config.json") as context:
        assert not context


def test_create_handle_success():
    with ManagerHandle(
        str(Path(__file__).parent / "load_order1.txt"),
        str(Path(__file__).parent / "config1.json"),
    ) as context:
        assert context

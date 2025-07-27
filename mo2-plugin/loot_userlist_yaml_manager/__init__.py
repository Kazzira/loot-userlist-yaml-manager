from mobase import IPlugin


def create_plugin() -> IPlugin:
    # Tempoary for now.
    class Plugin(IPlugin):
        pass

    return Plugin()

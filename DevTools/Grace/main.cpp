#include "Settings.h"
#include <AK/String.h>
#include <AK/Types.h>
#include <algorithm>
#include <cstring>
#include <stdio.h>

enum class PrimaryCommand : u8 {
    None = 0,
    Build,
    Config,
    Run
};

enum class ConfigSubCommand : u8 {
    None = 0,
    Get,
    Set,
    List
};

int main(int argc, char** argv)
{
    int minarg = 2;
    PrimaryCommand cmd = PrimaryCommand::None;
    ConfigSubCommand config_subcmd = ConfigSubCommand::None;

    if (argc >= minarg) {
        int arg_len = strlen(argv[1]);

        if (strncmp("build", argv[1], arg_len) == 0 && arg_len == 5) {
            minarg = 3;
            cmd = PrimaryCommand::Build;
        } else if (strncmp("config", argv[1], arg_len) == 0 && arg_len == 6) {
            cmd = PrimaryCommand::Config;
            ++minarg;
            if (argc >= minarg) {
                int subarg_len = strlen(argv[2]);
                if (strncmp(argv[2], "set", subarg_len) == 0 && subarg_len == 3) {
                    minarg = 5;
                    config_subcmd = ConfigSubCommand::Set;
                } else if (strncmp(argv[2], "get", subarg_len) == 0 && subarg_len == 3) {
                    minarg = 4;
                    config_subcmd = ConfigSubCommand::Get;
                } else if (strncmp(argv[2], "list", subarg_len) == 0 && subarg_len == 4) {
                    minarg = 3;
                    config_subcmd = ConfigSubCommand::List;
                } else {
                    minarg = -1;
                }
            }
        } else if (strncmp(argv[1], "run", arg_len) == 0 && arg_len == 3) {
            cmd = PrimaryCommand::Run;
            minarg = 2;
        }
    }

    if (argc < minarg || minarg < 0 || cmd == PrimaryCommand::None) {
        fprintf(stderr, "usage: \n");
        if (cmd == PrimaryCommand::None || (cmd == PrimaryCommand::Config && config_subcmd == ConfigSubCommand::None)) {
            fprintf(stderr, "  Config:\n");
            fprintf(stderr, "    Grace config list\n");
            fprintf(stderr, "    Grace config get <param>\n");
            fprintf(stderr, "    Grace config set <param> <value>\n");
        }
        if (cmd == PrimaryCommand::None || cmd == PrimaryCommand::Build) {
            fprintf(stderr, "  Build:\n");
            fprintf(stderr, "    Grace build <toolchain>\n");
            fprintf(stderr, "    Grace build <application>\n");
            fprintf(stderr, "    Grace build <image>\n");
        }
        if (cmd == PrimaryCommand::None || cmd == PrimaryCommand::Run) {
            fprintf(stderr, "  Run:\n");
            fprintf(stderr, "    Grace run [<image>]\n");
        }
        return 0;
    }

    fprintf(stderr, "1  whoop:\n");

    // needs always to be done
    Settings& settings = Settings::the();
    settings.load();

    fprintf(stderr, "2  whoop:\n");

    if (cmd == PrimaryCommand::Config) {
        switch (config_subcmd) {
        case ConfigSubCommand::Set: {
            break;
        }
        case ConfigSubCommand::List: {
            break;
        }
        case ConfigSubCommand::Get: {
            String parameter { argv[3], strlen(argv[3]) };
            String value;
            if (settings.get(parameter, &value)) {
                fprintf(stdout, "%s: %s", parameter.characters(), value.characters());
            } else {
                fprintf(stderr, "No valid parameter: %s\n", parameter.characters());
                return -1;
            }
            break;
        }
        case ConfigSubCommand::None:
        default: {
            return -1;
            break;
        }
        }
        return 0;
    }

    (void)(config_subcmd);
    //Toolchain::the().Load();

    // GeneratorPluginsLoader::the().Initialize(); // Find all loadable plugins and initialize them
    // GeneratorPluginsLoader::the().Generate(); // Generate everything

    return 0;
}
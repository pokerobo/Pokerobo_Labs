#include <Pokerobo_CLI.h>

CommandHandler cmdManager;

void cmd_func_info();
void cmd_func_logging();
void cmd_func_logging(int argc, char **argv);
void cmd_func_help();

cmd_t cmd_info("info", cmd_func_info);
cmd_t cmd_logging("log", cmd_func_logging);
cmd_t cmd_help("help", cmd_func_help);

void setup() {
  Serial.begin(57600);

  cmdManager.begin(&Serial);
  cmdManager.add(&cmd_info);
  cmdManager.add(&cmd_logging);
  cmdManager.add(&cmd_help);
}

void loop() {
  cmdManager.check();
  delay(100);
}

void cmd_func_info() {
  Serial.println("This is info command");
}

void cmd_func_logging(int argc, char **argv) {
  if (argc > 0) {
    if (strcmp(argv[0], "pause")) {
      Serial.println("logging is paused");
    } else if (strcmp(argv[0], "resume")) {
      Serial.println("logging is resumed");
    }
  }
}

void cmd_func_help() {
  Serial.println("Available commands: ");
  Serial.println(" - help");
  Serial.println(" - info");
}

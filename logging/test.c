
#include "logging.h"

int main(void)
{

	log_warning("Invalid attribute named %s", "INFO", "Sizwe");
	log_info("Invalid attribute named %s", "ERROR", "Position");
	log_error("Invalid attribute named %s", "WARNING", "rival");
	log_critical("Invalid attribute named %s", "CRITICAL", "Doom");
	return (0);
}

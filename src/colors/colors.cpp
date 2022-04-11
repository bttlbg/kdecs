#include "colors.hpp"

void writeColorScheme(kdecs_config kconf)
{
	/* Open the wal generated colors file */
	std::string wal_scheme_path(getenv("HOME"));
	wal_scheme_path.append("/.cache/wal/colors");
	std::fstream wal_scheme;
	wal_scheme.open(wal_scheme_path, std::ios::in);

	/* Open the color scheme file */
	std::string colorscheme_file_path(getenv("HOME"));
	colorscheme_file_path.append("/.local/share/color-schemes/kdecs.colors");
	std::fstream plasma_color_scheme;
	plasma_color_scheme.open(colorscheme_file_path, std::ios::in | std::ios::out);

	wal_colors colors;

	/* There's no reason to continue of the files we need are missing */
	if (!wal_scheme)
	{
		syslog(LOG_NOTICE, "Wal colors file missing");
	}
	else if (!plasma_color_scheme)
	{
		syslog(LOG_NOTICE, "Color scheme file missing");
	}
	else
	{
		/* The first line is always the background */
		std::getline(wal_scheme, colors.background);
		std::getline(wal_scheme, colors.accent);

		/*for (int i = 0; i < atoi(kconf.accent.c_str()); i++)
		{
			syslog(LOG_NOTICE, "for");
			//if (!wal_scheme.eof())
				std::getline(wal_scheme, colors.accent);
		}*/

		syslog(LOG_NOTICE, colors.background.c_str());
		syslog(LOG_NOTICE, colors.accent.c_str());
	}

	wal_scheme.close();
	plasma_color_scheme.close();

	return;
}
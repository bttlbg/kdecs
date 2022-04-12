#include "colors.hpp"

//int convertHEX(const char *num)
std::string convertHEX(const char *num)
{
	int len = strlen(num);
	int base = 1;
	int temp = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		if (num[i] >= '0' && num[i] <= '9')
		{
			temp += (num[i] - 48) * base;
			base = base * 16;
		}
		else if (num[i] >= 'A' && num[i] <= 'F')
		{
			temp += (num[i] - 55) * base;
			base = base * 16;
		}
	}

	char t[5];
	sprintf(t, "%d", temp);
	//syslog(LOG_NOTICE, num);
	//syslog(LOG_NOTICE, t);
	std::string tt = t;
	//return temp;
	return tt;
}

void writeColorScheme()
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
		std::string trash_line;
		for (int i = 0; !wal_scheme.eof(); i++)
		{
			if (i == 0)
				std::getline(wal_scheme, colors.background);

			else if (i == 1)
				std::getline(wal_scheme, colors.accent);

			else if (i == 7)
				std::getline(wal_scheme, colors.foreground);
			else
				std::getline(wal_scheme, trash_line);
		}

		for (int j = 0, i = 1; i < (int)colors.background.length(); i = i + 2, j++)
		{
			std::string aux_str = "";
			aux_str += toupper( colors.background.at(i));
			aux_str += toupper( colors.background.at(i + 1));
			colors.background_rgb[j] = convertHEX(aux_str.c_str());
		}

		for (int i = 1, j = 0; i < (int)colors.accent.length(); i = i + 2, j++)
		{
			std::string aux_str = "";
			aux_str += toupper( colors.accent.at(i));
			aux_str += toupper( colors.accent.at(i + 1));
			colors.accent_rgb[j] = convertHEX(aux_str.c_str());
		}
		for (int i = 1, j = 0; i < (int)colors.foreground.length(); i = i + 2, j++)
		{
			std::string aux_str = "";
			aux_str += toupper( colors.foreground.at(i));
			aux_str += toupper( colors.foreground.at(i + 1));
			colors.foreground_rgb[j] = convertHEX(aux_str.c_str());
		}
		syslog(LOG_NOTICE, colors.background_rgb[0].c_str());
	}

	wal_scheme.close();
	plasma_color_scheme.close();

	return;
}

# include <iostream>
# include <dirent.h>

std::string		directory_contents( char * directory_path )
{
	DIR				*dh;
	struct dirent	*contents;
	std::string		pathString(directory_path);
	std::string		finalResult;

	dh = opendir ( directory_path );

	 if ( !dh )
	{
		return (NULL);
	}
	while ( ( contents = readdir ( dh ) ) != NULL )
	{
		std::string name = contents->d_name;
		std::string line;
		line = "<a href=\"" + pathString + "/" + name + "\">" + name + "</a>\n";
		finalResult += line;
	}
	closedir ( dh );
	return (finalResult);
}
int		main ()
{
	std::string		res;
	res = directory_contents ( (char*) "./www/tester" );
	if (res.size() > 0)
		std::cout << res << std::endl;
	return 0;
}

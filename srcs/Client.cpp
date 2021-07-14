#include "../includes/Client.hpp"

Client::Client()
{
    endConnexion = false;
}

Client::~Client()
{
}

int Client::sendall(int s, const char *buf, int *len)
{
    int total = 0;        // how many bytes we've sent
    int bytesleft = *len; // how many we have left to send
    int n;

    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    *len = total; // return number actually sent here

    return n==-1?-1:0; // return -1 on failure, 0 on success
} 

void    Client::readRequest()
{
    bool     first_recv = true;
    int     nbytes = 4096;

    while (nbytes == 4096)
    {
        nbytes = recv(fd, buf, 4096, 0);
        if (first_recv && nbytes == 0)
        {
            endConnexion = true;
            printf("Client on fd %d has closed connexion\n", fd);
        }
        if (nbytes < 0)
        {
            perror("recv");
            endConnexion = true;
        }
        first_recv = false;
        requestString += buf;
    }
    if (!endConnexion)
        parseRequestString();
}

void    Client::parseRequestString()
{
    std::stringstream   requestStream(requestString);
    std::string         line;

    std::getline(requestStream, line);
    parseFirstLine(line);

    std::cout << "method: " << request.method << std::endl;
    std::cout << "uri: " << request.uri << std::endl;
    std::cout << "protocol: " << request.protocol << std::endl;

    parseHeaders(requestStream);

	std::cout << "method: " << request.method << std::endl;
    std::cout << "uri: " << request.uri << std::endl;
    std::cout << "protocol: " << request.protocol << std::endl << std::endl;
	std::map<std::string, std::string>::iterator it = request.headers.begin();
	for (; it != request.headers.end(); it++)
		std::cout << it->first << " -> " << it->second << std::endl; 
}

int    Client::parseFirstLine(std::string line)
{
    std::vector<std::string>    words;
    std::string                 word;
    std::stringstream           lineStream(line);

    while (std::getline(lineStream, word, ' '))
    {
        if (line.size() > 0)
            words.push_back(word);
    }
    if (words.size() != 3)
        return (-1);
    request.method = words[0];
    request.uri = words[1];
    request.protocol = words[2];
    return (0);
}

int		Client::parseHeaders(std::stringstream &requestStream)
{
	std::string		line;

	while (std::getline(requestStream, line))
	{
		if (line.size() == 0)
		{
			request.body = requestStream.str();
			break ;
		}
		parseHeaderLine(line);
	}
	return (0);
}

int		Client::parseHeaderLine(std::string line)
{
	std::string			name;
	std::string			value;
	std::stringstream	lineStream(line);

	if (line.find(':') == std::string::npos)
		return (-1);
	std::getline(lineStream, name, ':');
	std::getline(lineStream, value);
	if (value[0] == ' ')
		value.erase(0, 1);
	
	request.headers.insert(std::make_pair(name, value));
	return (0);
}

/*Pseudo code:

parse request line,
    split on space: if 3 word ok, else problem.

    then split each line on : until empty line or EOF.
    EOF: no body.
    empty line: parse body
*/
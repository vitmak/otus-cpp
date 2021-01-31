#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            if (line.empty())
                break;

            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        enum IP_ADDR_LENGTH {
            IPv4 = 4,
            IPv6 = 6
        };

        // Returns true if 'lhs' ip - address is greater then 'rhs' ip - address.
        auto isIPAddrGreater = [](const std::vector<std::string>& lhs, const std::vector<std::string>& rhs)->bool {
            for (auto i = 0; i < IP_ADDR_LENGTH::IPv4; ++i)
            {
                if (std::stoi(lhs[i]) > std::stoi(rhs[i]))
                    return true;
                else if (std::stoi(lhs[i]) < std::stoi(rhs[i]))
                    return false;
            }
            return false;
        };

        // Reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), isIPAddrGreater);

        for(std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        
        auto filter = [&ip_pool,ip_length = IP_ADDR_LENGTH::IPv4](std::initializer_list<uint8_t> ip_parts)->std::vector<std::vector<std::string>> {
            if (ip_parts.size() > ip_length)
            {
                //TODO: Add throw "Uncorrect IP - address type."
            }

            std::vector<std::vector<std::string>> filteredIP;

            if (ip_pool.empty())
                return filteredIP;

            for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
            {
                auto isFilterOk = true;
                int ip_partIndices = 0;
                for (auto ip_part = ip_parts.begin(); ip_part != ip_parts.end(); ++ip_part, ++ip_partIndices)
                {
                    if (ip->at(ip_partIndices) != std::to_string(*ip_part))
                    {
                        isFilterOk = false;
                        break;
                    }
                }

                if (isFilterOk)
                {
                    filteredIP.push_back(*ip);
                }
            }

            return filteredIP;
        };
        
        // filter by first byte and output
        const auto &&filtered_ip1 = filter({ 1 });
        for (std::vector<std::vector<std::string> >::const_iterator i = filtered_ip1.cbegin(); i != filtered_ip1.cend(); ++i)
        {
            for (std::vector<std::string>::const_iterator ip_part = i->cbegin(); ip_part != i->cend(); ++ip_part)
            {
                if (ip_part != i->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        const auto&& filtered_ip2 = filter({ 46, 70 });
        for (std::vector<std::vector<std::string> >::const_iterator i = filtered_ip2.cbegin(); i != filtered_ip2.cend(); ++i)
        {
            for (std::vector<std::string>::const_iterator ip_part = i->cbegin(); ip_part != i->cend(); ++ip_part)
            {
                if (ip_part != i->cbegin())
                {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

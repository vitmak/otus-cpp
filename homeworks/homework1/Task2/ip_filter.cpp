#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>


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

// Reading IP addresses from a file.
std::vector<std::vector<std::string>> ReadIPAddressesFromFile(const std::string& path) {
    std::ifstream fin;
    fin.open(path);

    if (!fin.is_open()) {
        throw std::runtime_error{ "File open error!" };
    }

    std::vector<std::vector<std::string>> ip_pool;

    std::string line;
    while (!fin.eof()) {
        line = "";
        std::getline(fin, line);

        std::vector<std::string> v = split(line, '\t');
        if (!v.at(0).empty()) {
            ip_pool.push_back(split(v.at(0), '.'));
        }
    }

    return ip_pool;
}

int main()
{
    try
    {
        // Use this code to read data from console
        std::vector<std::vector<std::string> > data;

        for(std::string line; std::getline(std::cin, line);)
        {
            if (line.empty())
                break;

            std::vector<std::string> v = split(line, '\t');
            data.push_back(split(v.at(0), '.'));
        }

        // Use this code to read data from file ip_filter.TSV
        //auto data = ReadIPAddressesFromFile("..\\ip_filter.TSV");
        
        enum class IP_ADDR_LENGTH {
            IPv4 = 4,
            IPv6 = 6
        };

        // Checks IP addresses for the correctness of the following data:
        // - version compliance(IPv4 for our case);
        // - range of values([0..255]).
        auto checkIP = [](const std::vector<std::vector<std::string>>&ip_pool, size_t sizeOfIP) {
            for (auto it_pool = ip_pool.cbegin(); it_pool != ip_pool.cend(); ++it_pool)
            {
                if (it_pool->size() != sizeOfIP) {
                    throw std::runtime_error{ "Invalid IP address: IPv4 required." };
                }
                
                for (auto it_part = it_pool->cbegin(); it_part != it_pool->cend(); ++it_part) {
                    if (std::stoi(*it_part) < 0 || std::stoi(*it_part) > 255) {
                        throw std::runtime_error{ "Incorrect IP address value." };
                    }
                }
            }
        };

        checkIP(data, static_cast<size_t>(IP_ADDR_LENGTH::IPv4));

        using ip_address = std::vector<uint8_t>;

        // Convert from std::vector<std::vector<std::string>> to std::vector<std::vector<uint8_t>>
        auto conv = [](const std::vector<std::vector<std::string> >& source) {
            std::vector<ip_address> ip_pool;
            ip_pool.reserve(source.size());

            if (source.empty()) {
                return ip_pool;
            }

            for (auto ip = source.cbegin(); ip != source.cend(); ++ip) {
                std::vector<uint8_t> ip_addr(4);
                for (size_t ip_part = 0; ip_part != ip->size(); ++ip_part) {
                    ip_addr[ip_part] = static_cast<uint8_t>(std::stoi(ip->at(ip_part)));
                }
                ip_pool.push_back(ip_addr);
            }

            return ip_pool;
        };

        auto ip_pool = conv(data);

        // Returns true if 'lhs' ip - address is greater then 'rhs' ip - address.
        auto isIPAddrGreater = [](const ip_address& lhs, const ip_address& rhs)->bool {
            for (auto i = 0; i < static_cast<int>(IP_ADDR_LENGTH::IPv4); ++i)
            {
                if (lhs[i] > rhs[i])
                    return true;
                else if (lhs[i] < rhs[i])
                    return false;
            }
            return false;
        };

        // Reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), isIPAddrGreater);

        // Print IP addresses to console.
        auto print_IP_addresses = [](const std::vector<ip_address>& ip_pool) {
            for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
            {
                for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
                {
                    if (ip_part != ip->cbegin())
                    {
                        std::cout << ".";
                    }
                    std::cout << static_cast<int>(*ip_part);
                }
                std::cout << std::endl;
            }
        };

        print_IP_addresses(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // Filters the IP addresses stored in ip_pool. Returns a vector of IP addresses that match the filtering conditions.
        // ip_parts - contains filters for each byte of the IP address.The index in the ip_parts list determines the byte order of the IP address to filter.
        auto filter = [&ip_pool,ip_length = IP_ADDR_LENGTH::IPv4](std::initializer_list<uint8_t> ip_parts)->std::vector<ip_address> {
            if (ip_parts.size() > static_cast<size_t>(ip_length))
            {
                throw std::runtime_error{"Uncorrected filter of ip address."};
            }

            std::vector<ip_address> filteredIP;
            filteredIP.reserve(ip_pool.size());

            if (ip_pool.empty())
                return filteredIP;

            for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
            {
                auto isFilterOk = true;
                int ip_partIndices = 0;
                for (auto ip_part = ip_parts.begin(); ip_part != ip_parts.end(); ++ip_part, ++ip_partIndices)
                {
                    if (ip->at(ip_partIndices) != *ip_part)
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
        auto filtered_ip = filter({ 1 });
        print_IP_addresses(filtered_ip);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        filtered_ip = filter({ 46, 70 });
        print_IP_addresses(filtered_ip);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // filter by any byte and output
        auto filter_any = [&ip_pool](std::initializer_list<uint8_t> ip_parts)->std::vector<std::vector<uint8_t>> {
            std::vector<std::vector<uint8_t>> filteredIP;
            filteredIP.reserve(ip_pool.size());

            if (ip_pool.empty())
                return filteredIP;

            for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
            {
                for (auto it_filter = ip_parts.begin(); it_filter != ip_parts.end(); ++it_filter)
                {
                    auto it_find = std::find(ip->cbegin(), ip->cend(), *it_filter);
                    if (it_find != ip->end())
                    {
                        filteredIP.push_back(*ip);
                        break;
                    }
                }
            }

            return filteredIP;
        };

        // filter by any byte and output
        filtered_ip = filter_any({ 46 });
        print_IP_addresses(filtered_ip);

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
    catch (...) {
        std::cerr << "Unknown exception!" << std::endl;
    }

    return 0;
}

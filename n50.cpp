#include <iostream>
#include <vector>
#include <numeric>
#include <random>
#include <chrono>

int main()
{
    std::vector<uint64_t> lens;
    uint64_t n = 10000;
    
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1,100000); // range
    for (int i=0; i<n; ++i)
    	lens.push_back(dist(rng));

    // naive
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<uint64_t> lensCpy = lens;
    std::sort(lensCpy.begin(), lensCpy.end(), std::greater<uint64_t>());
    
	double halfSum = (double) std::accumulate(lensCpy.begin(), lensCpy.end(), 0) / 2;
	uint64_t cumSum = 0, n50 = 0;
	
	for (uint64_t i : lensCpy) {
		cumSum += i;
		if (cumSum >= halfSum) {
		std::cout << +i << std::endl;
			break;
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() << std::endl;
	
	// quickSelect
	start = std::chrono::high_resolution_clock::now();
	cumSum = 0;
	while (lens.size() > 1) {
	
		std::vector<uint64_t> v1, v2;
		uint64_t sum1 = 0, sum2 = 0;
		double pivot = (double) std::accumulate(lens.begin(), lens.end(), 0) / lens.size();
		//double pivot = lens[0];
		
		//std::cout << +pivot << std::endl;
		
		for (uint64_t i : lens) {
			if (i < pivot) {
				v1.push_back(i);
				sum1 += i;
			} else {
				v2.push_back(i);
				sum2 += i;
				}
		}
		
		if (sum2 + cumSum > halfSum) {
			lens = v2;
		}else{
			lens = v1;
			cumSum += sum2;
		}
		//for (uint64_t i : lens)
			//std::cout << +i << ",";
		//std::cout << std::endl;
	}
	std::cout << lens[0] << std::endl;
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << duration.count() << std::endl;
    return 0;
}
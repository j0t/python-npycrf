#include <boost/serialization/split_member.hpp>
#include "parameter.h"
#include "../sampler.h"

namespace npycrf {
	namespace crf {
		Parameter::Parameter(){

		}
		Parameter::~Parameter(){

		}
		Parameter::Parameter(double weight_size, double lambda_0, double sigma){
			_bias = 0;
			_weights = array<double>(weight_size);
			for(int i = 0;i < weight_size;i++){
				_weights[i] = sampler::uniform(-0.0001, 0.0001);
			}
			_lambda_0 = lambda_0;
			_sigma = sigma;
		}
		int Parameter::get_num_features(){
			return _weights.size();
		}
		void Parameter::print_distribution(){
			hashmap<int, int> distribution;
			int min_value = 0;
			int max_value = 0;
			for(int i = 0;i < _weights.size();i++){
				double abs_value = std::abs(_weights[i]);
				if(abs_value == 0){
					continue;
				}
				int log10_value = (int)log10(abs_value);
				distribution[log10_value] += 1;
				if(min_value == 0 || log10_value < min_value){
					min_value =  log10_value;
				}
				if(max_value == 0 || log10_value > max_value){
					max_value =  log10_value;
				}
			}
			for(int d = max_value;d >= min_value;d--){
				std::cout << pow(10, d) << "	" << distribution[d] << std::endl;
			}
		}
		template <class Archive>
		void Parameter::serialize(Archive &ar, unsigned int version)
		{
			boost::serialization::split_member(ar, *this, version);
		}
		template void Parameter::serialize(boost::archive::binary_iarchive &ar, unsigned int version);
		template void Parameter::serialize(boost::archive::binary_oarchive &ar, unsigned int version);
		void Parameter::save(boost::archive::binary_oarchive &ar, unsigned int version) const {
			int size = _weights.size();
			ar & size;
			for(int k = 0;k < size;k++){
				ar & k;
				ar & _weights[k];
			}
			ar & _bias;
			ar & _lambda_0;
		}
		void Parameter::load(boost::archive::binary_iarchive &ar, unsigned int version) {
			int size = 0;
			ar & size;
			_weights = array<double>(size);
			for(int n = 0;n < size;n++){
				int k;
				double value;
				ar & k;
				ar & value;
				_weights[k] = value;
			}
			ar & _bias;
			ar & _lambda_0;
		}
	}
}
#pragma once
#include <boost/python.hpp>
#include <vector>
#include <cassert>
#include "../npycrf/solver/sgd.h"
#include "dataset.h"
#include "npycrf.h"
#include "dictionary.h"

namespace npycrf {
	namespace python {
		class Trainer{
		private:
			std::vector<int> _rand_indices_train_u;
			std::vector<int> _rand_indices_train_l;
			std::vector<int> _rand_indices_dev_u;
			std::vector<int> _rand_indices_dev_l;
			Dataset* _dataset_l;	// CRFの学習用教師データ
			Dataset* _dataset_u;	// NPYCRFの学習用教師なしデータ
			Dictionary* _dict;
			NPYCRF* _npycrf;
			solver::SGD* _sgd;
			double* _vpylm_sampling_probability_table;
			wchar_t* _vpylm_sampling_id_table;
			bool* _added_to_npylm_u;
			bool* _added_to_npylm_l;
			void _print_segmentation(int num_to_print, std::vector<Sentence*> &dataset, std::vector<int> &rand_indices);
			double _compute_perplexity(std::vector<Sentence*> &dataset);
			double _compute_log_likelihood(std::vector<Sentence*> &dataset, bool labeled = false);
			void _gibbs_labeled();
		public:
			Trainer(Dataset* dataset_l, Dataset* dataset_u, Dictionary* dict, NPYCRF* npycrf, double crf_regularization_constant);
			void remove_all_data();
			void add_labeled_data_to_npylm();
			void gibbs(bool include_labeled_data = false);
			void sgd(double learning_rate, int batchsize = 32, bool pure_crf = false);
			void sample_hpylm_vpylm_hyperparameters();
			void sample_npylm_lambda();
			wchar_t sample_word_from_vpylm_given_context(wchar_t* context_ids, int context_length, int sample_t, bool skip_eow = false);
			void update_p_k_given_vpylm();
			double compute_perplexity_train();
			double compute_perplexity_dev();
			double compute_log_likelihood_labeled_train();
			double compute_log_likelihood_unlabeled_train();
			double compute_log_likelihood_labeled_dev();
			double compute_log_likelihood_unlabeled_dev();
			boost::python::list compute_precision_and_recall_labeled_dev();
			void print_segmentation_labeled_train(int num_to_print);
			void print_segmentation_unlabeled_train(int num_to_print);
			void print_segmentation_labeled_dev(int num_to_print);
			void print_segmentation_unlabeled_dev(int num_to_print);
			int detect_hash_collision(int max_word_length);
		};
	}
}
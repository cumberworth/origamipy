// enumerator.h

#ifndef ENUMERATOR_H
#define ENUMERATOR_H

#include "parser.h"
#include "domain.h"
#include "origami_system.h"
#include "files.h"
  
using namespace Parser;
using namespace DomainContainer;
using namespace Origami;
using namespace Files;

void print_matrix(vector<vector<double>> matrix);

class ConformationalEnumerator {
    public:
        ConformationalEnumerator(OrigamiSystem& origami_system);
        void enumerate();
        void set_staples(vector<pair<int, int>>);
        vector<Domain*> add_growthpoint(
                int new_c_ident,
                int new_d_i,
                Domain* old_domain);
        void remove_growthpoint(
                Domain* old_domain);
        vector<vector<double>> bound_state_weights();

        unordered_map<Domain*, Domain*> m_growthpoints {};
  
        // Weights of states defined by number of staples (x) and number of
        // fully bound domain pairs (Y)
        vector<vector<double>> m_bound_state_weights {};

    private:
        void enumerate_domain(Domain* domain, VectorThree p_prev);
        void set_growthpoint_domains(Domain* domain, VectorThree p_new);
        void set_bound_domain(Domain* domain, VectorThree p_new);
        void set_unbound_domain(Domain* domain, VectorThree p_new);
        void grow_next_domain(Domain* domain, VectorThree p_new);
        void create_domains_stack();
        void create_staple_stack(Domain* domain);
        double calc_multiplier(Domain* domain, Domain* other_domain);
        int count_involved_staples(Domain* domain);
        void calc_and_save_weights();
  
        OrigamiSystem m_origami_system;
  
        // Identity to unique indices
        unordered_map<int, vector<int>> m_identity_to_indices {};

        // Domain stack for growing
        vector<Domain*> m_domains;

        // Previous growthpoint position
        VectorThree m_prev_growthpoint_p;

        // Total system energy
        double m_energy {0};

        // Partition function
        double m_partition_f {0};

        double m_multiplier {1};
        double m_prefix {1};
};
  
class GrowthpointEnumerator {
    public:
        GrowthpointEnumerator(
                ConformationalEnumerator& conformational_enumerator,
                // Pairs of identity, number of copies
                vector<pair<int, int>> staples,
                OrigamiSystem& origami_system);
        void enumerate();

    private:
        bool growthpoints_repeated();

        ConformationalEnumerator& m_conformational_enumerator;
  
        // Pairs of identity, number of copies
        vector<pair<int, int>> m_staples {};
        vector<Domain*> m_unbound_system_domains {};
        OrigamiSystem m_origami_system;

        // Chain identity, domain index
        vector<pair<pair<int, int>, pair<int, int>>> m_growthpoints {};
        vector<vector<pair<pair<int, int>, pair<int, int>>>> m_enumerated_growthpoints {};
};
  
#endif // ENUMERATOR_H
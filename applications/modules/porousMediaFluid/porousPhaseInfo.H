#ifndef porousPhaseInfo_H
#define porousPhaseInfo_H

#include <variant>
#include <map>
#include <optional>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/undirected_graph.hpp>

#include "volFieldsFwd.H"
#include "solidThermophysicalTransportModel.H"

namespace Foam {

struct equilibriumHeatTransfer {
};
struct nonEquilibriumHeatTransfer {
    dimensionedScalar heatTransferCoefficient;
    dimensionedScalar effectiveSpecificSurfaceArea;
};
using heatTransfer = std::variant<equilibriumHeatTransfer, nonEquilibriumHeatTransfer>;

heatTransfer parse_heatTransfer(const dictionary& dict);

class porousPhaseInfo {
public:
    static const word FLUID_PHASE_NAME;

    struct phaseTransferProperty {
        heatTransfer heatTransfer;
    };

    using heatTransferGraph_type = 
    boost::adjacency_list<boost::vecS,boost::vecS,
        boost::undirectedS, std::string, phaseTransferProperty, boost::no_property>;

    struct porousPhase {
        volScalarField alpha;
        autoPtr<solidThermo> thermo;
        autoPtr<solidThermophysicalTransportModel> thermophysicalTransport;
        heatTransferGraph_type::vertex_descriptor vertex{};
    };


protected:
    std::map<word, porousPhase> porousPhases_;

    heatTransferGraph_type heatTransferGraph_;
    heatTransferGraph_type::vertex_descriptor fluid_vertex{};


public:
    explicit porousPhaseInfo(fvMesh&mesh, const Time& runTime);

    porousPhaseInfo(const porousPhaseInfo&)=delete;
    
    ~porousPhaseInfo()=default;

    auto& porousPhases() & {
        return porousPhases_;
    }
    
    const auto& porousPhases() const & {
        return porousPhases_;
    }

    bool isValidPhase(const word& phaseName) const {
        return this->porousPhases_.contains(phaseName) or (phaseName==FLUID_PHASE_NAME);
    }
    //- List of thermal equilibrium phases
    std::vector<std::vector<word>> thermalEquilibriumPhases() const;

    heatTransferGraph_type::vertex_descriptor vertexOfPhase(const word& phaseName) const;

    const heatTransfer * heatTransferBetween(const word& phaseA, const word& phaseB) const;

    const nonEquilibriumHeatTransfer * nonEquilibriumHeatTransferBetween(const word& phaseA, const word& phaseB) const;


    struct heatTransferInfoNode {
        struct heatTransferSource {
            size_t phaseA_index;
            word phaseB_name;
            const nonEquilibriumHeatTransfer& heatTransferInfo;
        };

        std::vector<word> thermalEquilibriumPhaseNames;
        std::vector<heatTransferSource> heatTransferSources;
    };
    std::vector<heatTransferInfoNode> heatTransferSummary() const;
};

}

#endif //porousPhaseInfo_H
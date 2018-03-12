// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  0, uint256("0x5de1108cd698eeb8fd017f52e35ac21e3bdc3f0dc653e7b1e3863c073b0be978"))
	(  250, uint256("0xd5a9daab580deb9df051942d3ade23d8dd22a97f02df461177a5c09dc8826e75"))
        (  500, uint256("0x2fd5314477abcd169aeea331bfa2fe533b522e8b127f252916156a89b2d47a5b"))
        (  750, uint256("0x42e8b1f51c106ac651253bf5f0da52af5740532a4a2b9d330fc2fa69fecf623b"))
        (  1000, uint256("0x2a4bea485c6651d270d98a4eda54fedf5f2c422aa8d511444f67a638b2cefc85"))
        (  1250, uint256("0xd25cd1bb66112a8be397b233e0789b8804724d5ca1a0db2f5a9c413c13e0b9cc"))
        (  1500, uint256("0x59e032fd50ecd748ea46ccce1bd8b9b9ccdb8be62488df7abb97cfd5151fafa2"))
        (  1750, uint256("0x90913fc0d9e129ff32a716885adc39920cdc4d1d6d5dc78944af70e595eb62ff"))
        (  2000, uint256("0x205bf1b577aa2d30fd55d14f22c6e0478cfed2948310b7946055214fc1a9a26f"))
        (  2250, uint256("0xec6a7fa356f58f0d9de39dc1575be64b2df3c3ff647a7e1539b0d66609833740"))
        (  2500, uint256("0xa4457a1769941f8e73794cae069bc2323b39fc7b06c70da7dadacdfe01f12df5"))
        (  2700, uint256("0x897c2f29558c5e643e4e1f27eff9d5af9872b25b33398a683449db15d4216203"))
        (  3000, uint256("0xe08d064900a1e98e6dec34241b5ae8cf454f9c8b1f160c7908d0777da4b8cb08"))
        (  3250, uint256("0xbbeb51dae681ae6106ca8462e4e2efb681415d9b8311634d92dfc5bfe4e50561"))
        (  3500, uint256("0x5f6f4176c5ea574769506ce70cc2b4fb5071d7fe09d95fa3dc26c588c287d020"))
        (  3750, uint256("0x4baa8db2fdae554b941a6c56bfc7c89c4a46c6d89d86c7fda9456f207a94b5e5"))
        (  4000, uint256("0xebfc63c562919242ee257bc9b590681468e34cd3e02906ea2d512b9ec81d04cc"))
        (  4250, uint256("0x5f42f1379879960b2c4b22364b0b70d98abcf3231bf07cf798e1e5f47eaccf07"))
        (  4500, uint256("0xb1891b1f8601f54ce6dbf419ff514f109be50ab48b24e4161a19536c4a532053"))
        (  4750, uint256("0x6e50b1b6605889ce65ba0f2d9097b5e4e9b7344ace392fa9aaa2ef22fe724c7c"))
        (  5000, uint256("0xbfa4965a5b14e218567f3c5c3c6aaf0f21d86ee3d8c9fa1ecd576efc569de524"))
        (  5250, uint256("0x301527e0bf7d1fc0087a43ee1d206e817ce87495edc9fed5e207cc3c4eaea1b4"))
        (  5500, uint256("0x104ef7a19691db5914a504a0ba86dec39597cfcd7098a5226911a1181563c3b1"))
        (  5700, uint256("0xfceeaf69302f2a71056d636c4b24c361c8e3e8f56947bd020c30006e65a47a92"))
        (  5734, uint256("0x91422b6b39dcb189eeb12459d66b5dff163140668b32ad5f012998cafe62e391"))
        (  5740, uint256("0xc1ed5f2821739a6fb3e1f71f8c37e746ac69ebabb6b55ff33c083ea06eaa9be0"))
        (  5800, uint256("0x40940297a98aebaf11ccfe94a58e4e1ce6c64634b4c0fb7610448ba5bc7804cd"))
        (  6000, uint256("0x3826531bd1f8488109946a29d7e6c6d2d4500a31c86e8566939d20472bc9c20e"))
   ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1519793938, // * UNIX timestamp of last checkpoint block
        6001,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        1000.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (   0, uint256("0x"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        //1365458829,
        //547,
        //576
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}

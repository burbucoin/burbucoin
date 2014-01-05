// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 burbucoin Developers

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

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     0, uint256("0x7ee74d87729abaf37150b7125cca1dd9e0ea0295355cec57ba063c6c2b10cffa"))
            (     1, uint256("0x1667f0fd4c1a6ddafd73f9f25224a494b6af374b64eca28a500dc30395db2a99"))
            (     2, uint256("0x0b59985b03ab0ee1f680fb30f891faae8a728d7d38b45b43e290596ad000c7ca"))
            (     3, uint256("0x1fc886f3cc7cb4a250a9a801ee3d1570d10d79809b3ac9f9de26de58ee32905d"))
            (     10, uint256("0x8199038d8d9d0d33349ebb333b56a22773c5c98df92fc612b1e7e75c29d84042"))
            (     100, uint256("0x34504e740ba79e972a3de477e0dcbca888208d1aad6daffdfcbee988f495f084"))
            (     200, uint256("0x468284693cfca9cbe4435b673d0d6abd7db04684ddf332d37e796a6b7102e216"))
            (     300, uint256("0x000a5334c6f335631575f74715ace88729864e92ce12b12cbea3b6c63e9b792f"))
            ;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}

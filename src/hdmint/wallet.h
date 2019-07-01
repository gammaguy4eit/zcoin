// Copyright (c) 2019 The Zcoin Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZCOIN_HDMINTWALLET_H
#define ZCOIN_HDMINTWALLET_H

#include <map>
#include "libzerocoin/Zerocoin.h"
#include "hdmint/mintpool.h"
#include "uint256.h"
#include "primitives/zerocoin.h"
#include "wallet/wallet.h"


class CHDMint;

class CHDMintWallet
{
private:
    int32_t nCountLastUsed;
    std::string strWalletFile;
    CMintPool mintPool;
    uint160 hashSeedMaster;

public:
    int static const COUNT_LAST_USED_DEFAULT = 0;

    CHDMintWallet(std::string strWalletFile);

    bool ReadIsCrypted();
    bool WriteIsCrypted(bool isCrypted);
    bool SetHashSeedMaster(const uint160& hashSeedMaster, bool fResetCount=false);
    void SyncWithChain(bool fGenerateMintPool = true, boost::optional<std::list<std::pair<uint256, MintPoolEntry>>> listMints = boost::none);
    bool GenerateMint(const sigma::CoinDenomination denom, sigma::PrivateCoin& coin, CHDMint& dMint, boost::optional<MintPoolEntry> mintPoolEntry = boost::none);
    bool LoadMintPoolFromDB();
    bool RegenerateMint(const CHDMint& dMint, CSigmaEntry& zerocoin);
    bool IsSerialInBlockchain(const uint256& hashSerial, int& nHeightTx, uint256& txidSpend, CTransaction& tx);
    bool TxOutToPublicCoin(const CTxOut& txout, sigma::PublicCoin& pubCoin, CValidationState& state);
    void GenerateMintPool(int32_t nCountStart = 0, int32_t nCountEnd = 0);
    bool SetMintSeedSeen(MintPoolEntry& mintPoolEntry, const int& nHeight, const uint256& txid, const sigma::CoinDenomination& denom);
    bool SeedToZerocoin(const uint512& seedZerocoin, GroupElement& bnValue, sigma::PrivateCoin& coin);
    // Count updating functions
    int32_t GetCount();
    void SetCount(int32_t nCount);
    void UpdateCountLocal();
    void UpdateCountDB();
    void UpdateCount();

private:
    void GetZerocoinSeedData(MintPoolEntry& mintPoolEntry);
    uint512 CreateZerocoinSeed(MintPoolEntry& mintPoolEntry);
};

#endif //ZCOIN_HDMINTWALLET_H

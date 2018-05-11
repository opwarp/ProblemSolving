#ifndef _SORT_STRINGS_WITH_NEW_ALPHABET_H
#define _SORT_STRINGS_WITH_NEW_ALPHABET_H
#include "Debug.h"
/*
Lintcode: Word Sorting
Give a new alphabet, such as {c,b,a,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z}.
Sort the string array according to the new alphabet.
Given Alphabet = {c,b,a,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z}, String array = {cab,cba,abc}, return {cba,cab,abc}.
Explanation:
According to the new dictionary order, output the sorted result {cba, cab, abc}.
Given Alphabet = {z,b,a,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,c}, String array = {bca,czb,za,zba,ade}, return {zba,za,bca,ade,czb}.
Explanation:
According to the new dictionary order, output the sorted result {zba,za,bca,ade,czb}.

Leetcode: Custom Sort String
S and T are strings composed of lowercase letters.
In S, no letter occurs more than once.
S was sorted in some custom order previously.
We want to permute the characters of T so that they match the order that S was sorted.
More specifically, if x occurs before y in S, then x should occur before y in the returned string.
Return any permutation of T (as a string) that satisfies this property.
Example :
Input:
S = "cba"
T = "abcd"
Output: "cbad"
Explanation:
"a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a".
Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
Note:
S has length at most 26, and no character is repeated in S.
T has length at most 200.
S and T consist of lowercase letters only.
 */
class SortStringsWithNewAlphabet
{
public:
    SortStringsWithNewAlphabet(){}

    std::string SortString(const std::string & alpha, const std::string & word)
    {
        std::vector<int> count(26, 0);
        for (const auto & c : word)
            ++count[c-'a'];
        std::string res;
        for (const auto & c : alpha)
            while (count[c-'a']-- > 0)
                res += c;
        for (int i = 0; i < 26; ++i)
            while (count[i]-- > 0)
                res += (i+'a');
        std::cout << "SortStringsWithNewAlphabet for alpha=[" << alpha << "], word=[" << word << "]: " << res << std::endl;
        return res;
    }

    std::vector<std::string> SortStringArr(const std::string & alpha, const std::vector<std::string> & words)
    {
        int N = alpha.size();
        std::unordered_map<char,int> toIdx;
        for (int i = 0; i < N; ++i)
            toIdx[alpha[i]] = i;
        std::vector<std::string> res(words);
        std::sort(res.begin(), res.end(), [&](const std::string & s1, const std::string & s2)
        {
            int N = s1.size();
            int M = s2.size();
            int minLen = std::min(N, M);
            int i = 0;
            while (i < minLen)
            {
                int idx1 = toIdx[s1[i]];
                int idx2 = toIdx[s2[i]];
                if (idx1 < idx2)
                    return true;
                else if (idx1 > idx2)
                    return false;
                else
                    ++i;
            }
            if (i == N)
                return true;
            return false;
        });
        std::cout << "SortStringsWithNewAlphabet for alpha=[" << alpha << "], words=[" << Debug::ToStr1D<std::string>()(words) << "]: " << Debug::ToStr1D<std::string>()(res) << std::endl;
        return res;
    }

    std::vector<std::string> SortStringArr_Trie(const std::string & alpha, const std::vector<std::string> & words)//best
    {
        //1. build a trie with every word in words
        //where the trie node has children in new alphabet order

        //2. traverse the trie to output all words

        return std::vector<std::string>();
    }
};
/*
SortStringsWithNewAlphabet for alpha=[zyxwvutsr], word=[xrxuvwztvxzyurz]: zzzyxxxwvvuutrr
SortStringsWithNewAlphabet for alpha=[zyxwvutsr], words=[suzwy, rux, yrwu, tyzvx, rt, xvyr, r, uv, vs, w, y, z]: z, y, yrwu, xvyr, tyzvx, w, vs, uv, rt, suzwy, r, rux
 */
#endif
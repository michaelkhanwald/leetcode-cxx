/* Momenta2019秋招技术岗笔试题
企业提供原题
00:07:25
31/37
[编程题]k倍多重正整数集合

时间限制：1秒
空间限制：131072K

k 倍多重正整数集合的定义是：在一个多重集合（元素可以重复）中，不存在一个正整数是另一个正整数的k倍。
现在小M有 n 个正整数，你可以选择其中一些数构成 k 倍多重正整数集合。请求出最多能选出多少数来构成它。

输入描述:
第一行有两个整数 n, k (1 <= n <= 10^5, 1 <= k <= 10^9)。
接下来一行有 n 个正整数 a1, a2, ..., an (1 <= ai <= 10^9)。

输出描述:
最多能选出多少数构成k倍多重正整数集合。

输入例子1:
6 2
2 3 6 5 4 10

输出例子1:
3

例子说明1:
第一个样例中，我们选择2，3，5即可满足要求，因为k == 2，不存在一个数是另一个数的两倍。

输入例子2:
2 2
2 2

输出例子2:
2

例子说明2:
第二个样例中，我们选择2，2即可满足要求，因为k == 2，2也不是2的两倍，注意多重集合元素可以重复。
*/

#include <bits/stdc++.h>

using namespace std;

template<typename Type>
void printVector(vector<Type> vec) {
	cout << "[ ";
	for (size_t i=0; i<vec.size(); i++) {
		auto& val = vec[i];
		cout << val;
		if (i != vec.size()-1)
			cout << ", ";
	}
	cout << " ]" << endl;
}

enum {
	USED = 0x1,
	EXCLUDE = 0x2,
	K_MULTI = 0x4,
};

struct elem {
	using value_type = struct elem;
	int cnt;
	unsigned flag;
	elem(int cnt2, unsigned flag2 = 0U) : cnt(cnt2), flag(flag2)
	{
	}
};

class Solution
{
public:
	map<int, elem> constructCntSet(vector<int> &vec, int k)
	{
		map<int, elem> valmap;
		for (ssize_t i = vec.size()-1; i >= 0; /* i++ */) {
			int cnt = 0;
			for (ssize_t j = i; j >= 0; j--) {
				if (vec[j] == vec[i])
					++cnt;
				else
					break;
			}
			auto it = valmap.find(vec[i]*k);
			unsigned flag = 0U;
			if (it != valmap.end()) {
				flag = K_MULTI;
				it->second.flag = K_MULTI;
			}
			valmap.emplace(vec[i], elem(cnt, flag));
			i -= cnt;
		}
		return valmap;
	}
	int filterValMap(map<int, elem> &valmap)
	{
		int cnt = 0;
		for (auto it = valmap.begin(); it != valmap.end(); ) {
			if (!(it->second.flag & K_MULTI)) {
				cnt += it->second.cnt;
				it = valmap.erase(it);
			} else {
				++it;
			}
		}
		return cnt;
	}
	int maxKMultiSubSet(map<int, elem> &valmap, map<int, elem>::iterator it, int k, bool prevUsed)
	{
		if (it == valmap.end())
			return 0;
		it->second.flag |= EXCLUDE;
		int nval = k * it->first;
		auto nit = valmap.find(nval);
		if (prevUsed) {
			return maxKMultiSubSet(valmap, nit, k, false);
		} else {
			int useThisRet = it->second.cnt + maxKMultiSubSet(valmap, nit, k, true);
			int skipThisRet = maxKMultiSubSet(valmap, nit, k, false);
			return max(useThisRet, skipThisRet);
		}
	}
	int maxKMultiSet_ex(map<int, elem> &valmap, int k)
	{
		int cnt = 0;
		for (auto it = valmap.begin(); it != valmap.end(); it++) {
			if (it->second.flag & EXCLUDE)
				continue;
			cnt += maxKMultiSubSet(valmap, it, k, false);
		}
		return cnt;
	}
	int maxKMultiSet(vector<int> &vec, int k)
	{
		//printVector(vec);
		sort(vec.begin(), vec.end());
		//cout << "vec front " << vec.front() << endl;
		if (vec.back()/vec.front() < k)
			return vec.size();

		map<int, elem> valmap = std::move(constructCntSet(vec, k));
		
		if (k == 1)
			return valmap.size();

		int fixedCnt = filterValMap(valmap);
		int setCnt = maxKMultiSet_ex(valmap, k);
		return fixedCnt + setCnt;
	}
};

int main()
{
	int n;
	int k;
	while (cin >> n >> k) {
		vector<int> vec(n);
		for (int i = 0; i < n; i++)
			cin >> vec[i];
		Solution sln;
		auto ret = sln.maxKMultiSet(vec, k);
		cout << ret << endl;
	}
}

#if 0
6 2
2 3 6 5 4 10
3

2 2
2 2
2

12 2
2 2 4 4 4 4 8 8 8 8 8 8
8

2 1
2 2
1

### case 20% ###
1000 2
155 257 26 248 155 16 116 171 93 254 120 114 91 234 14 142 166 115 140 144 61 202 181 132 89 254 248 149 126 166 200 252 187 230 223 147 185 187 65 94 80 257 88 249 232 201 201 146 62 60 187 116 156 164 183 188 194 51 1 58 23 201 236 162 12 130 38 188 69 118 260 102 52 19 217 61 125 227 30 40 21 29 219 27 181 209 85 259 22 171 23 217 171 19 70 252 19 117 177 178 106 78 133 99 126 233 203 155 170 70 71 138 153 209 102 220 212 222 83 90 254 70 110 68 174 250 203 31 20 65 103 226 9 181 33 177 248 120 226 257 7 97 68 254 32 55 5 219 33 151 191 206 232 87 175 68 230 105 3 14 65 23 245 39 250 198 103 106 5 36 2 34 85 73 5 239 254 197 203 220 104 211 126 194 163 184 40 144 168 89 70 95 231 218 211 64 149 106 245 34 134 140 222 212 9 64 253 82 18 54 219 151 146 219 182 206 225 212 131 243 119 92 222 96 35 230 226 83 35 57 159 245 141 184 118 206 68 127 104 35 220 238 234 202 99 129 126 107 31 176 99 198 20 168 104 46 161 95 82 140 181 219 260 38 124 39 35 118 209 96 246 137 31 25 182 187 192 30 206 192 243 259 95 178 153 231 10 223 79 201 50 203 194 234 183 29 119 71 198 46 101 20 29 192 231 259 230 226 26 97 101 30 3 229 146 230 24 114 180 77 105 52 175 257 43 31 5 80 108 60 153 217 136 53 27 192 164 148 36 194 83 252 11 242 26 83 90 33 221 69 78 218 82 192 67 187 74 8 105 191 204 165 114 178 98 88 256 203 183 203 198 35 245 252 177 238 25 158 91 9 113 40 106 8 2 46 47 172 225 20 186 184 15 223 258 179 234 26 57 126 249 109 235 132 172 143 61 51 163 57 131 225 2 227 31 53 4 32 25 93 189 76 60 69 94 100 29 205 27 194 177 47 220 207 248 134 153 21 110 222 62 21 124 112 46 104 234 178 132 32 189 84 2 23 26 248 127 167 93 60 67 18 177 60 155 216 162 167 94 235 103 205 204 205 175 44 31 99 4 65 55 252 184 251 106 56 124 125 21 188 18 45 19 175 68 193 84 69 11 80 259 32 17 96 64 194 93 111 102 222 142 240 159 260 159 13 189 131 100 118 156 33 238 215 176 139 124 157 144 245 177 247 190 238 75 203 93 29 245 215 73 2 157 111 121 80 120 161 222 186 239 13 166 190 201 101 163 51 17 209 187 135 171 191 57 249 2 173 233 203 93 159 55 24 169 157 177 142 207 140 45 75 150 196 41 15 194 17 166 16 170 138 97 90 116 229 96 105 188 9 179 106 199 186 202 232 27 101 215 66 117 139 196 121 130 223 28 80 187 218 106 141 139 220 193 160 74 159 83 4 102 179 47 32 162 105 128 24 215 236 149 190 38 140 125 235 211 101 64 114 18 54 223 219 173 86 104 14 32 108 114 126 145 62 28 194 182 224 102 238 217 147 213 196 23 97 22 227 87 105 101 116 117 173 124 221 38 84 248 133 103 145 200 149 29 172 194 6 72 16 253 251 53 120 105 133 111 68 6 229 56 90 85 238 142 84 223 83 21 47 55 154 106 184 248 142 118 120 210 158 36 98 242 259 166 112 42 159 133 208 17 167 194 38 214 26 112 111 108 91 153 232 36 143 81 244 223 113 224 250 65 183 195 57 112 195 30 161 205 13 74 218 178 41 123 172 119 259 137 172 145 106 76 71 61 97 236 25 150 9 80 123 11 172 92 139 63 30 128 190 225 123 127 3 100 93 78 97 60 164 121 244 69 27 39 251 71 4 147 170 97 237 128 134 154 70 2 232 86 173 183 254 90 10 253 172 73 54 69 128 79 18 179 18 246 245 224 225 113 243 176 118 180 94 251 1 175 21 104 61 206 82 163 244 224 239 172 31 246 242 241 98 184 128 12 65 152 90 175 238 35 219 216 168 248 253 194 219 127 13 131 30 24 35 68 84 211 117 135 209 50 94 190 128 110 138 112 68 8 107 98 27 79 173 70 80 186 214 126 247 157 227 29 202 228 81 2 61 103 98 182 135 83 136 96 150 76 220 7 99 143 43 13 4 8 258 136 112 106 24 151 142 158 99 81 121 45 97 124 107 65 183 163 146 251 121 166 138 254 254 175 193 232 167 134 19 142 219 156 38 107 142 243 170 210 77 196 129 223 29 155 231 17 204 121 157 78 4 90 24

724

#endif

#if 0
// sample solution from nowcoder, slightly faster than my solution
// see comment below

#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
 
int main() 
{
    int n, k, x;
    cin >> n >> k;
    map<int, int> Map;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        Map[x]++;
    }
    if (k == 1)
    {
        cout << Map.size() << endl;
    }
    else
    {
        int num;
        for (map<int, int>::iterator pt = Map.begin(); pt != Map.end(); pt++)
        {
            x = (pt->first)*k;
            if (Map.find(x) == Map.end())
            {
                continue;
            }
            if (pt->second == 0 || Map[x] == 0)
            {
                continue;
            }
            num = min(pt->second, Map[x]);
            n = n - num;  // remove k multiple cnt
            Map[x] = Map[x] - num;  // remove k multiple cnt
        }
        cout << n << endl;
    }
 
    return 0;
}

#endif
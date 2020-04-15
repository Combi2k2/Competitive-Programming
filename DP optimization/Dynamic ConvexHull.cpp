bool Q;
struct Line {
	mutable ll  s, c, p;
    bool operator < (const Line& t) const   {
        return Q ? p < t.p : s > t.s;
    }
};

struct ConvexHull : multiset<Line>  {
	const ll    inf = LLONG_MAX;
	ll  div(ll a,ll b)  {
		return a / b - ((a ^ b) < 0 && a % b);
	}
	bool isect(itr x,itr y) {
		if(y == end())  {
			x -> p = inf;
			return 0;
		}
		if(x -> s == y -> s)
			x -> p = x -> c < y -> c ? inf : -inf;
		else
			x -> p = div(y -> c - x -> c,x -> s - y -> s);
		return x -> p >= y -> p;
	}
	
	void add(ll s,ll c) {
		auto it2 = insert({s,c,0});
		auto it1 = it2++;
		auto it0 = it1;
		while(isect(it1,it2))   it2 = erase(it2);
		if(it0 != begin() && isect(--it0,it1))
			isect(it0,it1 = erase(it1));
		while((it1 = it0) != begin() && (--it0) -> p >= it1 -> p)
			isect(it0,erase(it1));
	}
	ll  query(ll x) {
		assert(!empty());
		Q = 1;  auto l = *lower_bound({0,0,x});
		Q = 0;
		return l.s * x + l.c;
	}
};

//Functions definations for gmap class

template<typename K, typename V>
V& gmap<K, V>::operator[](K& key)
{
    return mp [ & key ];
}

template<typename K, typename V>
const bool gmap<K, V>::ispresent(K& key)
{
    return mp.find( & key ) != mp.end();
}
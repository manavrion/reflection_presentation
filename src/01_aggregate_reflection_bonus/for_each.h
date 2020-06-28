namespace magic_io::detail {

template <typename T, typename Func>
void for_each_by_members(T&& t, Func&& f) {
  template for (auto&& member : t) { f(member); }
}

}  // namespace magic_io::detail

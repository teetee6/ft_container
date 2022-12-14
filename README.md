https://stackedit.io/app# 에서 작업

# Description

컨테이너 함수들은 공통적으로, 필요 시 마다 동적으로 원소들을 메모리 생성 후 값 할당, 값 파괴 및 메모리해제등의 작업이 일어나므로,  std::allocator<_Tp> 변수 하나를 두어, 이걸로 관리 상기 작업을 처리
## vector
내부적으로 pointer 변수로 상태관리를 하다가, 필요시마다 iterator(pointer)형식으로 wrap_iterator를 이용해서 이터레이터를 반환 <br/>
> wrap_iterator : 이 또한 내부적으로 pointer변수로 상태관리를 함. <br/>
> 다만, 다양한 연산자오버로딩 및 기능들 (+, -, ++, +=, ->, *, ==)을 미리 포인터끼리 연산하여 작동하게 해둔 도구 <br/>

- void  reserve(size_type  __n) <br/>
현재 내 capacity보다 __n이 더 <b>클때만</b> 공간만 확장하는것임. <br/>
기존 데이터 새로운 공간에 다 옮기고, 기존 데이터 해지. <br/>

- void  resize(size_type  __sz, const_reference  __x = value_type()) <br/>
현재 사이즈가 __sz보다 크면 shrink (뒤에서부터 파괴), <br/>
현재 사이즈가 __sz보다 작으면 extend <br/>
---> extend시 enough memory면 그냥 뒤에 줄줄이 양방향으로 연결 <br/>
---> extend시 reallocate가 필요하면 <b>기존 용량의 2배</b>(1회이상 반복) 후, 기존 데이터 새로운 공간에 다 옮기고, 새로운 데이터 양방향으로 연결 ((기존 데이터 공간 해지) <br/>

- void  push_back(const_reference  __x) <br/>
---> enough memory면 뒤에 연결 <br/>
---> reallocate시 <b>기존 용량의 2배</b>(비어있을시 1) 후, reserve() 후 값 construct. <br/>

- void  assign(_InputIterator  __first, _InputIterator  __last, 스피네) <br/>
---> enough memory면 first~~~last만큼 construct <br/>
---> reallocate시 <b>first~~~last 공간만큼만 용량</b>에 넣은 후,  값 construct. <br/>

- void  assign(size_type  __n, const_reference  __u) <br/>
---> reallocate시 <b>__n 공간만큼만 용량</b>에 넣은 후,  값 construct. <br/>

- iterator  insert(iterator  __position, const_reference  __x) <br/>
---> enough memory면 end-1에서부터 __position이 나올때까지 내려가며 하나씩 홉을 뒤로 당김(값 복사) <br/>
---> reallocate시 <b>기존 용량의 2배</b>(비어있을시 1) 후,  기존꺼 복사+__position위치 값+기존꺼 복사  <br/>

- void  insert(iterator  __position, size_type  __n, const_reference  __x) <br/>
---> enough memory면 end-1에서부터 __position이 나올때까지 내려가며 __n단위로 홉을 뒤로 당김(값 복사) 후, __n개 construct <br/>
---> reallocate시 <b>기존 용량 + __n만큼 용량에 넣음 후, 결과size보다 작으면 계속 2배 반복</b> 후,  기존꺼 복사+__position위치 값+기존꺼 복사  <br/>

- void  insert(iterator  __position, _InputIterator  __first, _InputIterator  __last, 스피네) <br/>
---> enough memory면 end-1에서부터 __position이 나올때까지 내려가며 __n(__last - __first)단위로 홉을 뒤로 당김(값 복사) 후, __n개 construct <br/>
---> reallocate시 <b>용량이 결과size보다 작으면 계속 2배 반복(용량이 0이면 딱 __n만큼만 함)</b> 후,  기존꺼 복사+__position위치 값+기존꺼 복사  <br/>

- iterator  erase(iterator  __position) <br/>
---> return (erase(__position, __position + 1)); <br/>

- iterator  erase(iterator  __first, iterator  __last) <br/>
---> __first부터 시작해서 __n단위로 홉을 앞으로 당기다가, end()를 마주치면 end갱신 후, 이전 end가 나올떄까지 다시 진행해가며 destroy <br/>

## map
---> std::map::value_compare ? std::map::value_type(std::pair<>)을 비교(key값끼리 비교)하는 함수 객체
사용법을 자꾸 까먹는 함수
```c++
int main() {
    ft::map<int, std::string> Map;
    ft::pair<int, std::string> a(3, "good"), b(5, "bye");
    std::cout << Map.value_comp()(a, b) << std::endl;   // 기본 비교함수 ft::less
    std::cout << ft::_Select1st<ft::pair<int, std::string> >()(a) << std::endl; // ft::pair의 first를 반환해주는 함수
    std::cout << ft::_Identity<int>()(777) << std::endl;  // 자기 자신을 반환함
}
```


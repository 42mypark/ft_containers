# ft_containers

C++98의 STL을 직접 구현해보며 그 구조를 학습한 프로젝트입니다.

## Implemented features
- vector
- map
- stack
- iterator
- enable_if

## What I've learned
- SFINAE(Substitution Failure Is Not An Error)
  - enable_if
- Internal structure of containers
  - vector: dynamically allocated array
  - map: RB tree
  - stack: linear container adaptor
- Exception guarantee

# Alice 

This is an implementation of [justinas/alice](https://github.com/justinas/alice) in C++.

Alice provides a convenient way to chain 
your middleware functions.

In short, it transforms

```C++
Middleware1(Middleware2(Middleware3(param1,param2,param3)))
```

to

```C++
Chain(Middleware1, Middleware2, Middleware3).Then(make_tuple(param1,param2,param3))
```

### Why?

None of the other middleware chaining solutions
behaves exactly like Alice.
Alice is as minimal as it gets:
in essence, it's just a for loop that does the wrapping for you.

Check out [this blog post](http://justinas.org/alice-painless-middleware-chaining-for-go/)
for explanation how Alice is different from other chaining solutions.

### Usage

Your middleware functions should have the form of

```C++
tuple<param1&&, param2&&, ...> func (param1&&, param2&&, ...)
```

### Contributing

0. Find an issue that bugs you / open a new one.
1. Discuss.
2. Branch off, commit, test.
3. Make a pull request / attach the commits to the issue.

### Inspired by 
[justinas/alice](https://github.com/justinas/alice)

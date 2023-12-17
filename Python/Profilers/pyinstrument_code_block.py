from cProfile import Profile
import pyinstrument_call_stack
with Profile(interval=0.1) as profiler:
    pyinstrument_call_stack.estimate_pi(n=10_000_000)



profiler.print()



profiler.open_in_browser()
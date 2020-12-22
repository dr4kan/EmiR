#ifndef EmiR_OOB_h
#define EmiR_OOB_h

/// Possible treatment of out-of-boundary solutions:
/// - PBC: Periodic Boundary Condition
/// - RBC: Reflective Boundary Condition
/// - BAB: Back At boundaries
/// - DIS: Disregard the solution and generate a new one
enum OOBMethod {PBC, RBC, BAB, DIS};

#endif

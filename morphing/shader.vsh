vs_1_1
dcl_position v0            
def c6, 1,0,0,0      
dcl_color v1               
mov oD0, v1
dp3     r0, v0, v0          
rsq     r0, r0              
mul     r0, r0, c1          
sub     r0, r0, c6   
mul     r0, r0, c0          
add     r0, r0, c6  
mul     r1.xyz, v0.xyz, r0.x
mov     r1.w,   v0.w        
m4x4    oPos, r1, c2

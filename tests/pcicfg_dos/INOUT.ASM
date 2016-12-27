.386

_TEXT     segment para public 'CODE' use16
          assume cs:_TEXT, ss:NOTHING

          ;
          ; Those functions are exported.
          ;
          public _inpd
          public _outpd

          ;
          ; Stack frames for C functions.
          ;
inpdstk   struc
oldbp     dw  ?
retaddr   dw  ?
inport    dw  ?
inpdstk   ends

outpdstk  struc
oldbp     dw  ?
retaddr   dw  ?
outport   dw  ?
data      dd  ?
ourpdstk  ends

          ;
          ; unsigned long inpd(unsigned short inport);
          ;
_inpd     proc  near
  push  bp
  mov   bp,sp
  mov   dx,[bp].inport
  in    eax,dx
  mov   edx,eax
  shr   edx,16
  pop   bp
  ret
_inpd     endp

          ;
          ; void outpd(unsigned short outport, unsigned long data);
          ;
_outpd    proc  near
  push  bp
  mov   bp,sp
  mov   dx,[bp].outport
  mov   eax,[bp].data
  out   dx,eax
  pop   bp
  ret
_outpd    endp

_TEXT     ends
          end

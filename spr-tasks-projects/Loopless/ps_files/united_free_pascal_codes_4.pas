program sort(input,output);
var
a,b,c,d,e : integer;
begin
  readln(a,b,c,d,e);
  if a < b then
    if b < c then
      if c < d then
        if d < e then
          writeln(a,b,c,d,e)
        else if c < e then
          writeln(a,b,c,e,d)
        else if b < e then
          writeln(a,b,e,c,d)
        else if a < e then
          writeln(a,e,b,c,d)
        else
          writeln(e,a,b,c,d)
      else if b < d then
        if c < e then
          writeln(a,b,d,c,e)
        else if d < e then
          writeln(a,b,d,e,c)
        else if b < e then
          writeln(a,b,e,d,c)
        else if a < e then
          writeln(a,e,b,d,c)
        else
          writeln(e,a,b,d,c)
      else if a < d then
        if c < e then
          writeln(a,d,b,c,e)
        else if b < e then
          writeln(a,d,b,e,c)
        else if d < e then
          writeln(a,d,e,b,c)
        else if a < e then
          writeln(a,e,d,b,c)
        else
          writeln(e,a,d,b,c)
      else
        if c < e then
          writeln(d,a,b,c,e)
        else if b < e then
          writeln(d,a,b,e,c)
        else if a < e then
          writeln(d,a,e,b,c)
        else if d < e then
          writeln(d,e,a,b,c)
        else
          writeln(e,d,a,b,c)
    else if a < c then
      if b < d then
        if d < e then
          writeln(a,c,b,d,e)
        else if b < e then
          writeln(a,c,b,e,d)
        else if c < e then
          writeln(a,c,e,b,d)
        else if a < e then
          writeln(a,e,c,b,d)
        else
          writeln(e,a,c,b,d)
      else if c < d then
        if b < e then
          writeln(a,c,d,b,e)
        else if d < e then
          writeln(a,c,d,e,b)
        else if c < e then
          writeln(a,c,e,d,b)
        else if a < e then
          writeln(a,e,c,d,b)
        else
          writeln(e,a,c,d,b)
      else if a < d then
        if b < e then
          writeln(a,d,c,b,e)
        else if c < e then
          writeln(a,d,c,e,b)
        else if d < e then
          writeln(a,d,e,c,b)
        else if a < e then
          writeln(a,e,d,c,b)
        else
          writeln(e,a,d,c,b)
      else
        if b < e then
          writeln(d,a,c,b,e)
        else if c < e then
          writeln(d,a,c,e,b)
        else if a < e then
          writeln(d,a,e,c,b)
        else if d < e then
          writeln(d,e,a,c,b)
        else
          writeln(e,d,a,c,b)
    else
      if b < d then
        if d < e then
          writeln(c,a,b,d,e)
        else if b < e then
          writeln(c,a,b,e,d)
        else if a < e then
          writeln(c,a,e,b,d)
        else if c < e then
          writeln(c,e,a,b,d)
        else
          writeln(e,c,a,b,d)
      else if a < d then
        if b < e then
          writeln(c,a,d,b,e)
        else if d < e then
          writeln(c,a,d,e,b)
        else if a < e then
          writeln(c,a,e,d,b)
        else if c < e then
          writeln(c,e,a,d,b)
        else
          writeln(e,c,a,d,b)
      else if c < d then
        if b < e then
          writeln(c,d,a,b,e)
        else if a < e then
          writeln(c,d,a,e,b)
        else if d < e then
          writeln(c,d,e,a,b)
        else if c < e then
          writeln(c,e,d,a,b)
        else
          writeln(e,c,d,a,b)
      else
        if b < e then
          writeln(d,c,a,b,e)
        else if a < e then
          writeln(d,c,a,e,b)
        else if c < e then
          writeln(d,c,e,a,b)
        else if d < e then
          writeln(d,e,c,a,b)
        else
          writeln(e,d,c,a,b)
  else
    if a < c then
      if c < d then
        if d < e then
          writeln(b,a,c,d,e)
        else if c < e then
          writeln(b,a,c,e,d)
        else if a < e then
          writeln(b,a,e,c,d)
        else if b < e then
          writeln(b,e,a,c,d)
        else
          writeln(e,b,a,c,d)
      else if a < d then
        if c < e then
          writeln(b,a,d,c,e)
        else if d < e then
          writeln(b,a,d,e,c)
        else if a < e then
          writeln(b,a,e,d,c)
        else if b < e then
          writeln(b,e,a,d,c)
        else
          writeln(e,b,a,d,c)
      else if b < d then
        if c < e then
          writeln(b,d,a,c,e)
        else if a < e then
          writeln(b,d,a,e,c)
        else if d < e then
          writeln(b,d,e,a,c)
        else if b < e then
          writeln(b,e,d,a,c)
        else
          writeln(e,b,d,a,c)
      else
        if c < e then
          writeln(d,b,a,c,e)
        else if a < e then
          writeln(d,b,a,e,c)
        else if b < e then
          writeln(d,b,e,a,c)
        else if d < e then
          writeln(d,e,b,a,c)
        else
          writeln(e,d,b,a,c)
    else if b < c then
      if a < d then
        if d < e then
          writeln(b,c,a,d,e)
        else if a < e then
          writeln(b,c,a,e,d)
        else if c < e then
          writeln(b,c,e,a,d)
        else if b < e then
          writeln(b,e,c,a,d)
        else
          writeln(e,b,c,a,d)
      else if c < d then
        if a < e then
          writeln(b,c,d,a,e)
        else if d < e then
          writeln(b,c,d,e,a)
        else if c < e then
          writeln(b,c,e,d,a)
        else if b < e then
          writeln(b,e,c,d,a)
        else
          writeln(e,b,c,d,a)
      else if b < d then
        if a < e then
          writeln(b,d,c,a,e)
        else if c < e then
          writeln(b,d,c,e,a)
        else if d < e then
          writeln(b,d,e,c,a)
        else if b < e then
          writeln(b,e,d,c,a)
        else
          writeln(e,b,d,c,a)
      else
        if a < e then
          writeln(d,b,c,a,e)
        else if c < e then
          writeln(d,b,c,e,a)
        else if b < e then
          writeln(d,b,e,c,a)
        else if d < e then
          writeln(d,e,b,c,a)
        else
          writeln(e,d,b,c,a)
    else
      if a < d then
        if d < e then
          writeln(c,b,a,d,e)
        else if a < e then
          writeln(c,b,a,e,d)
        else if b < e then
          writeln(c,b,e,a,d)
        else if c < e then
          writeln(c,e,b,a,d)
        else
          writeln(e,c,b,a,d)
      else if b < d then
        if a < e then
          writeln(c,b,d,a,e)
        else if d < e then
          writeln(c,b,d,e,a)
        else if b < e then
          writeln(c,b,e,d,a)
        else if c < e then
          writeln(c,e,b,d,a)
        else
          writeln(e,c,b,d,a)
      else if c < d then
        if a < e then
          writeln(c,d,b,a,e)
        else if b < e then
          writeln(c,d,b,e,a)
        else if d < e then
          writeln(c,d,e,b,a)
        else if c < e then
          writeln(c,e,d,b,a)
        else
          writeln(e,c,d,b,a)
      else
        if a < e then
          writeln(d,c,b,a,e)
        else if b < e then
          writeln(d,c,b,e,a)
        else if c < e then
          writeln(d,c,e,b,a)
        else if d < e then
          writeln(d,e,c,b,a)
        else
          writeln(e,d,c,b,a)
end.


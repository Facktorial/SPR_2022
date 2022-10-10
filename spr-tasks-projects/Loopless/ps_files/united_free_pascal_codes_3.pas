program sort(input,output);
var
a,b,c,d : integer;
begin
  readln(a,b,c,d);
  if a < b then
    if b < c then
      if c < d then
        writeln(a,b,c,d)
      else if b < d then
        writeln(a,b,d,c)
      else if a < d then
        writeln(a,d,b,c)
      else
        writeln(d,a,b,c)
    else if a < c then
      if b < d then
        writeln(a,c,b,d)
      else if c < d then
        writeln(a,c,d,b)
      else if a < d then
        writeln(a,d,c,b)
      else
        writeln(d,a,c,b)
    else
      if b < d then
        writeln(c,a,b,d)
      else if a < d then
        writeln(c,a,d,b)
      else if c < d then
        writeln(c,d,a,b)
      else
        writeln(d,c,a,b)
  else
    if a < c then
      if c < d then
        writeln(b,a,c,d)
      else if a < d then
        writeln(b,a,d,c)
      else if b < d then
        writeln(b,d,a,c)
      else
        writeln(d,b,a,c)
    else if b < c then
      if a < d then
        writeln(b,c,a,d)
      else if c < d then
        writeln(b,c,d,a)
      else if b < d then
        writeln(b,d,c,a)
      else
        writeln(d,b,c,a)
    else
      if a < d then
        writeln(c,b,a,d)
      else if b < d then
        writeln(c,b,d,a)
      else if c < d then
        writeln(c,d,b,a)
      else
        writeln(d,c,b,a)
end.


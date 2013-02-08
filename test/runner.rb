fork do
 i = 0 
  (1...1000000).each { |n| i += n }
end 
`ruby child.rb`
#sleep 20

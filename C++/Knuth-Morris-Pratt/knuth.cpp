#include <iostream>
#include <vector>
using namespace std;
 
int main(){
 
	string prefix = "dolor";
	vector<int>prefixfunctie (prefix.size(),0);
 
	for (int i = 1; i < prefix.size(); i++)
	{
		int k = prefixfunctie[i - 1];
 
		while (k > 0 && prefix[i] != prefix[k])
			k = prefixfunctie[k - 1];
 
		if (prefix[i] == prefix[k])
			k++;  
 
		prefixfunctie[i] = k;                                                                                                                                                                                                                
	}
 
	string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam vitae diam urna, in elementum ante. Sed imperdiet leo nisi. Etiam sollicitudin nisl et purus commodo sodales. Etiam et tortor volutpat ligula tincidunt vestibulum. Duis sodales neque eu sem mollis ac sollicitudin quam iaculis. Duis accumsan mi nec dolor semper sagittis. Aliquam dictum enim in ipsum blandit facilisis. Integer at massa eu massa molestie sollicitudin.Donec pulvinar metus quis nulla suscipit dapibus. Fusce urna diam, rutrum a porta id, dictum vel lectus. Nulla facilisi. Mauris ut nulla sit amet elit tempor convallis eget et tellus. Vivamus nec sem sem, venenatis sodales dui. Fusce eget quam sed tortor venenatis lobortis. Donec mollis, est non ultricies porta, lacus leo auctor est, et venenatis orci ligula nec tellus. Nam consectetur nulla at urna placerat nec posuere risus lobortis. Nullam cursus commodo metus non blandit. Pellentesque sed nulla augue. Curabitur ornare accumsan egestas.auris eget mi enim. Nulla iaculis tristique ante, sed consectetur arcu luctus eu. Praesent et turpis at elit ultrices luctus sed ut lorem. Ut elit libero, scelerisque at dignissim id, eleifend eget nunc. Cras vehicula tellus ut augue scelerisque tincidunt. Integer sed nibh elit, vitae pulvinar elit. Sed eget magna id lectus tincidunt egestas. Morbi lobortis ultrices augue, at interdum diam hendrerit ac. Donec rhoncus, diam eu volutpat pulvinar, dui arcu fermentum tortor, in condimentum nisi metus quis erat. Vestibulum dui mi, consequat ornare eleifend vitae, dignissim condimentum orci. Fusce sed turpis erat, eget auctor leo. Phasellus commodo commodo sodales. Fusce fringilla velit id enim dictum sit amet accumsan arcu tristique. Suspendisse potenti. Ut vulputate commodo neque ut aliquam. Nam arcu neque, dictum eget blandit in, adipiscing nec augue.nteger faucibus pretium pretium. Nunc at velit sit amet lorem porta pulvinar vitae vel felis. Quisque imperdiet nibh ac mi tincidunt vel aliquam leo facilisis. Suspendisse in augue facilisis nisi elementum volutpat. Donec non lorem eleifend sapien facilisis accumsan at auctor diam. Etiam quis lorem a purus blandit vestibulum non id tortor. Vivamus ut accumsan odio. Morbi quam nisi, mollis id volutpat eu, aliquam non massa. Nunc rutrum lacinia scelerisque. Curabitur posuere dapibus neque id lobortis. Duis sodales gravida pulvinar. Integer interdum felis mi, a bibendum ipsum. Morbi ac mauris felis, sed pharetra odio. Aliquam bibendum metus at ligula laoreet consectetur. Morbi tellus magna, placerat in consectetur at, blandit adipiscing orci.Nunc quis neque mi, sit amet sollicitudin leo. Vestibulum mollis ullamcorper est. Curabitur vitae risus elit, a auctor elit. In id sem mi, at ultricies ipsum. Suspendisse molestie quam in magna molestie id aliquet nulla volutpat. Vivamus nulla nunc, ullamcorper sed mollis eget, lobortis in urna. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Praesent in purus nec lorem sodales tristique ut vel mi. Vivamus pellentesque imperdiet felis, vitae adipiscing nisl pulvinar eu. Donec interdum scelerisque lectus, nec tristique mauris rutrum et. Vivamus in sem augue, non hendrerit lectus. Pellentesque et lorem vel turpis gravida eleifend nec ac diam. Nam at metus id ante pretium hendrerit sed nec sem.Phasellus magna nulla, dapibus ut bibendum et, ultrices eu diam. Mauris tristique condimentum metus, at mollis turpis sollicitudin id. Cras magna risus, lobortis sed gravida quis, volutpat dapibus tortor. Praesent porta, erat lacinia blandit dictum, magna ligula porttitor augue, molestie convallis metus arcu ornare nibh. Nullam a magna tristique ligula vulputate sagittis at vitae sem. Morbi id molestie massa. Aliquam non mauris a ante egestas vestibulum eget sed odio. Aenean nec risus arcu, et posuere purus. Vivamus accumsan lacinia sagittis. Proin quis pretium lorem. Mauris venenatis tristique metus eu vestibulum. Nunc neque magna, tempus vel cursus ac, ultricies vitae purus.Donec cursus condimentum adipiscing. Nunc eu nisl ac sem adipiscing sodales. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Etiam ac diam vel turpis cursus facilisis id ac dolor. Vestibulum nec felis sed mauris aliquet faucibus. Cras et eros sit amet diam fringilla molestie. Aliquam suscipit suscipit quam et elementum. Pellentesque rutrum, nisi sed mollis porttitor, nunc mi laoreet magna, eu euismod nisl massa sed ipsum. Aliquam erat volutpat. Maecenas dapibus gravida mauris quis placerat. Vivamus vitae aliquet enim. Etiam vel lacus non libero scelerisque fermentum lobortis eget diam.Maecenas erat odio, lacinia quis auctor et, rutrum non lectus. Integer sodales dictum ipsum id accumsan. Donec augue felis, condimentum eget posuere non, consequat vitae ligula. Maecenas sed felis magna. Praesent consequat est vel mi ultricies vitae sodales ligula fermentum. Mauris sagittis libero vitae ante pharetra commodo. Aliquam varius lacus vitae justo gravida egestas. Integer feugiat sodales mi, vitae blandit lectus commodo non. Sed volutpat tempus porttitor. Duis diam augue, tempor ut adipiscing ut, viverra non tortor. In hac habitasse platea dictumst. Fusce nec velit quis leo suscipit eleifend dignissim non purus. Pellentesque quis magna neque.Ut scelerisque sollicitudin est at suscipit. Sed lorem erat, suscipit ac blandit vitae, fermentum adipiscing orci. Quisque vestibulum felis odio. Morbi tempus, ante non hendrerit rutrum, mauris massa aliquam orci, ut scelerisque odio eros quis orci. Aliquam ornare dictum molestie. Fusce et ante eros, eu convallis massa. Curabitur a nibh sapien. Vivamus vestibulum velit ac velit mollis tincidunt. Sed id lacus non risus vestibulum ullamcorper vel eu magna. Morbi magna erat, ornare consequat consectetur vel, congue vel eros. Maecenas rhoncus tempus quam vitae semper. Cras a elit risus. Nunc a metus orci. Cras vitae tristique tortor. Pellentesque tincidunt lectus at dolor malesuada sit amet tempus arcu interdumVestibulum a quam nibh. Mauris lobortis porttitor elit, id aliquam nisi facilisis ac. Nam velit quam, suscipit commodo pretium quis, dignissim sed mi. Donec eros tellus, gravida id posuere tristique, porttitor ut purus. Nullam dapibus ornare nulla eu pretium. Curabitur metus risus, vulputate a pharetra eu, facilisis ac enim. Nunc lorem elit, aliquet at tempus a, laoreet sed mi. Nunc pulvinar consequat dui, in semper est porttitor sodales. Vivamus venenatis cursus augue tempus imperdiet. Quisque faucibus eros at nulla pharetra vitae pulvinar augue pharetra. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Quisque euismod fermentum enim sit amet adipiscing.Nam in enim elit. Aliquam quis metus sed lorem malesuada accumsan. Vestibulum pretium tortor tincidunt metus lacinia pulvinar. Cras vulputate nunc sed eros vestibulum mattis. Sed venenatis dui a orci rutrum sodales. Sed aliquam vestibulum porttitor. Donec posuere suscipit nibh a hendrerit. In pharetra neque et ante auctor faucibus. Donec ante ligula, dapibus tincidunt suscipit eget, consequat ac elit. Nulla aliquam nunc faucibus eros sagittis sit amet fermentum ante rhoncus. Duis id urna quis ligula sollicitudin suscipit id vitae mauris. Pellentesque mauris tortor, aliquet quis lobortis sed, fermentum ac lorem. Sed egestas, risus sit amet posuere fringilla, dolor risus dapibus felis, id vulputate nisl libero vitae nunc.Fusce non lectus mi. Suspendisse at velit in quam hendrerit egestas. Nullam accumsan pulvinar velit, quis semper felis ultricies sed. Integer vestibulum aliquet neque vel imperdiet. Praesent vitae lectus et nulla dictum adipiscing sed sit amet lorem. Curabitur molestie, diam eget commodo lacinia, mi lorem facilisis urna, non tempor velit massa vitae enim. Morbi non nisi nulla. Maecenas varius dignissim libero. Quisque mattis nibh eu elit imperdiet ullamcorper. Donec at ullamcorper quam. Nulla lobortis mattis massa, tempor vulputate neque iaculis eu. Maecenas sollicitudin mattis luctus. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Donec laoreet mattis urna, et fringilla odio pretium at.Morbi molestie, libero vel egestas mattis, sapien tortor consequat ipsum, eu facilisis augue ligula vel lacus. Praesent eleifend, neque non rhoncus dignissim, magna mi molestie est, sit amet sagittis mauris enim non leo. Sed eu turpis risus, ut elementum diam. Sed nibh augue, sodales ac consequat eget, consequat eu nibh. Vivamus rhoncus scelerisque pharetra. Phasellus vestibulum mi quis quam auctor consectetur malesuada lacus sollicitudin. Suspendisse id laoreet dolor. Sed velit massa, ornare sed vulputate in, vestibulum vel nibh. In ac mauris nec leo tempor lobortis quis vitae nunc. Integer imperdiet sapien ut neque pulvinar blandit. Fusce nunc nisi, porttitor sed imperdiet vitae, tincidunt ac purus.Vestibulum eget magna vitae tellus pretium imperdiet eget tristique enim. Etiam placerat mattis tellus, eget elementum nisi ultricies non. Suspendisse faucibus eros a mauris molestie et pharetra dui elementum. Proin quis accumsan lorem. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Aliquam erat volutpat. Morbi elementum tincidunt rutrum. Duis convallis, diam quis vulputate imperdiet, sem enim aliquam tortor, sed iaculis metus purus a quam. Nulla at tempus elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer lacus nisi, elementum at varius vel, aliquet at lacus. Nulla vitae quam massa. Aliquam at arcu in mi dapibus dictum.Proin lacus velit, egestas eu molestie id, aliquet sit amet ligula. Duis malesuada, mauris eget tristique venenatis, leo arcu auctor erat, id euismod arcu nibh eu velit. Nullam sit amet ligula magna, quis vulputate odio. Nulla eget nulla posuere odio egestas fringilla vel eget risus. Mauris ac magna nisl, consectetur convallis orci. Proin vestibulum tortor et nisi facilisis sed hendrerit ligula rutrum nullam.";
	int aantal_prefixen = 0;
 
	int k = 0;
	for (int i = 0; i < text.size(); i++)
	{
		while(k > 0 && text[i] != prefix[k]) 
			k = prefixfunctie[k];
		k++;
		if(k == prefix.size()){
				aantal_prefixen++;
				k = prefixfunctie[k];
		}                                                                                                                                                                                                   
	}		
	cout << aantal_prefixen;
 
	return 0;
}
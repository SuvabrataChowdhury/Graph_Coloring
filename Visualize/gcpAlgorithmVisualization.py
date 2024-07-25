import math
from manim import *

class DisplayChromosome1(Scene):
	def construct(self):
		sequence = MathTex('Sequence;')
		seqLength = MathTex('Sequence\\_Length;').next_to(sequence,UP)
		numConflicts = MathTex('Number\\_of\\_Conflicts;').next_to(sequence,DOWN)
		fitness = MathTex('Fitness').next_to(numConflicts,DOWN)

		info = VGroup(sequence,seqLength,numConflicts,fitness)
		#info.scale(0.5)

		brace = Brace(info,[-1,0,0])

		label = MathTex('Chromosome',':=')
		label.next_to(brace,LEFT)

		chromosome=VGroup(info,label,brace)

		self.add(chromosome.move_to([0,0,0]).scale(0.9))

class DisplayChromosome2(Scene):
	def construct(self):
		c=[1,2,3,2,1]
		
		chrObj = Chromosome();

		sequence = chrObj.getChromosome(c)
		indices = chrObj.getIndices(sequence,1)
		seqLength = MathTex('Sequence\\_Length','=','5;').next_to(indices,UP)
		numConflicts = MathTex('Number\\_Of\\_Conflicts','=','1;').next_to(sequence,DOWN)
		fitness = MathTex('Fitness','=','\\times').next_to(numConflicts,DOWN)
		fitness[2].set_color(RED)

		info = VGroup(sequence,indices,seqLength,numConflicts,fitness)
		#info.scale(0.5)

		brace = Brace(info,[-1,0,0])

		label = MathTex('Chromosome',':=')
		label.next_to(brace,LEFT)

		chromosome=VGroup(info,label,brace)

		sequence[0][1].set_color(RED)
		sequence[1][1].set_color(GREEN)
		sequence[2][1].set_color(YELLOW)
		sequence[3][1].set_color(GREEN)
		sequence[4][1].set_color(RED)

		vertices = [i for i in range(1,6)]
		edges = [(1,4),(1,3),(2,5),(2,4),(3,5)]

		graph = Graph(vertices, edges, layout='circular', labels=True, vertex_config={1:{'fill_color':RED},2:{'fill_color':GREEN},3:{'fill_color':YELLOW},4:{'fill_color':GREEN},5:{'fill_color':RED}},edge_config={(2,4):{'stroke_color':RED}})

		items = VGroup(chromosome.move_to([0,0,0]).scale(0.9),graph.scale(0.8))
		items.arrange(RIGHT)

		self.add(items)

class Chromosome(Scene):
	def getChromosome(self,chromosome):
		resultChromosome=VGroup()
		resultChromosome.add(self.getBox(chromosome[0],ManimColor.from_hsv([chromosome[0]/max(chromosome),1,255])))

		for i in range(1,len(chromosome)):
			box=self.getBox(chromosome[i],ManimColor.from_hsv([chromosome[i]/max(chromosome),1,255]))
			box.shift(RIGHT*i)
			resultChromosome.add(box)
		
		resultChromosome.move_to((0,0,0))
		
		return resultChromosome

	def getBox(self,text,textColor):
		result=VGroup()

		box=Square(side_length=1,color=GRAY)
		text=Text(str(text),color=textColor).move_to(box.get_center())

		result.add(box,text)
		return result
	
	def getIndices(self,chromosome,startNum):
		indices=VGroup()

		for i in range(len(chromosome)):
			text=Text(str(i+startNum),font_size=20).next_to(chromosome[i],UP)
			indices.add(text)

		return indices

class Crossover(Scene):
	def construct(self):
		#Initial Chromosomes
		c1=[1,3,3,4,2,3,1,3,1,2]
		c2=[3,1,2,3,3,2,1,4,1,3]

		#Get chromosome MObjects
		#chromosome1 holds a vGroup genes and c1 holds a list of gene mobjects
		util=Chromosome()

		chromosome1 = util.getChromosome(c1)
		chromosome2 = util.getChromosome(c2)

		#Both chromosomes appear at the center
		self.play(FadeIn(chromosome1),FadeIn(chromosome2),run_time=0.5)
		#The first one goes up and second one comes down
		self.play(chromosome1.animate.shift(UP),chromosome2.animate.shift(DOWN),run_time=2)

		c1Label = MathTex('P_1:=').next_to(chromosome1,LEFT)
		c2Label = MathTex('P_2:=').next_to(chromosome2,LEFT)
		
		#Write the labels for c1 and c2 respectively
		self.play(Write(c1Label),Write(c2Label),run_time=2)
		
		#Create the indices
		indices1=util.getIndices(chromosome1)
		#indices1.next_to(chromosome1,UP)

		indices2=indices1.copy()
		indices2.next_to(chromosome2,UP)

		self.wait(0.5)

		#indices gets written
		self.play(Write(indices1),Write(indices2),run_time=2)
		self.wait(1)
		
		center1=chromosome1[2:7].get_center()
		center2=chromosome2[2:7].get_center()

		#move the selected genes up
		self.play(chromosome1[2:7].animate.shift(2*UP),chromosome2[2:7].animate.shift(2*DOWN))

		self.wait(1)
		
		#swap the selected genes into the others' position
		self.play(chromosome1[2:7].animate.move_to(center2),chromosome2[2:7].animate.move_to(center1),run_time=2)
		chromosome1[2:7],chromosome2[2:7]=chromosome2[2:7],chromosome1[2:7]

		#chromosomes=VGroup(chromosome1,chromosome2)
		self.wait(1)
		
		self.play(
			Transform(c1Label,MathTex("C_1:=").move_to(c1Label.get_center())),
			Transform(c2Label,MathTex("C_2:=").move_to(c2Label.get_center())),
			run_time=2
			)

		self.wait(1)

class Mutation(Scene):
	def construct(self):
		c1=[1,3,2,4,2,4,1,3,1,2]
		
		util=Chromosome()
		chromosome=util.getChromosome(c1)
		indices=util.getIndices(chromosome)

		c1Label=MathTex("C:=").next_to(chromosome,LEFT)

		self.play(FadeIn(chromosome),run_time=2)
		self.play(Write(indices),run_time=1)
		self.wait(0.5)
		self.play(Write(c1Label),run_time=2)
		self.wait(0.5)
		
		i=len(c1)//2-1
		
		self.play(indices[i].animate.set_weight(BOLD))

		self.wait(0.5)
		
		self.play(Transform(chromosome[i],util.getBox(3,ManimColor.from_hsv([3/max(c1),1,255])).move_to(chromosome[i].get_center())),run_time=2)
		self.wait(0.5)
		
		self.play(Transform(c1Label,MathTex("C^{\prime}:=").move_to(c1Label.get_center())))

		self.wait(1)

class Selection(Scene):
	def construct(self):

		fitnesses = [21,23,11,15,19,7,4]
		labels = VGroup()

		for i in range(0,len(fitnesses)):
			labels.add(MathTex('C_'+str(i),':=',str(fitnesses[i])))
		
		self.play(labels.animate.arrange(DOWN),run_time=2)
		self.play(labels.animate.to_edge(LEFT),run_time=2)

		self.wait(1)
		
		arcs=VGroup()
		startAngle=0.0
		radiusArc=2

		frameBox = SurroundingRectangle(labels[0])

		for index,fitness in enumerate(fitnesses):
			endAngle = 2*PI*fitness/sum(fitnesses)
			arc = Arc(radius=radiusArc,start_angle=startAngle,angle=endAngle,stroke_width=50,color=ManimColor.from_hsv([(index+1)/len(fitnesses),1,255]))
			arcs.add(arc)

			startAngle = startAngle+endAngle

			if index==0:
				self.play(Create(frameBox))
			else:
				frameBox1 = SurroundingRectangle(labels[index])
				self.play(Transform(frameBox,frameBox1))

			self.play(labels[index][0].animate.set_color(arc.get_color()))
			self.play(Create(arc))

		dot = Dot(color=BLACK).move_to((radiusArc)*UP)
		
		#selected={52,9,45,54,80,45}
		#nextChromosomes={C2,C0,C1,C2,C4,C1}

		self.play(Uncreate(frameBox))
		self.play(FadeIn(dot))
		self.play(Rotating(dot,about_point=[0,0,0],run_time=10))
		self.wait(1)

class MyGraph1(Scene):
	def construct(self):
		vertices = [i for i in range(1,6)]
		edges = [(1,4),(1,3),(2,5),(2,4),(3,5)]

		g_proper = Graph(vertices, edges, layout='circular', labels=True, vertex_config={1:{'fill_color':RED},2:{'fill_color':GREEN},3:{'fill_color':YELLOW},4:{'fill_color':BLUE},5:{'fill_color':RED}})

		g_improper = Graph(vertices, edges, layout='circular', labels=True, vertex_config={1:{'fill_color':RED},2:{'fill_color':GREEN},3:{'fill_color':YELLOW},4:{'fill_color':GREEN},5:{'fill_color':RED}},edge_config={(2,4):{'stroke_color':RED}})

		g_chromatic = Graph(vertices, edges, layout='circular', labels=True, vertex_config={1:{'fill_color':RED},2:{'fill_color':RED},3:{'fill_color':BLUE},4:{'fill_color':BLUE},5:{'fill_color':YELLOW}})

		self.add(g_chromatic)

class GraphImplementation(Scene):
	def construct(self):
		vertices = [i for i in range(1,6)]
		edges = [(1,4),(1,3),(2,5),(2,4),(3,5)]

		graph = Graph(vertices, edges, layout='circular', labels=True)

		edgeListLabel = VGroup()

		for i in range(0,len(edges)):
			if i!=len(edges)-1:
				edgeListLabel.add(MathTex('(',str(edges[i][0]),',',str(edges[i][1]),'),'))
			else:
				edgeListLabel.add(MathTex('(',str(edges[i][0]),',',str(edges[i][1]),')'))
		
		edgeListLabel.arrange(DOWN)
		edgeListLabel.add(Brace(edgeListLabel,[-1,0,0]),Brace(edgeListLabel,[1,0,0]))
		edgeListLabel.add(MathTex('edges',':=').next_to(edgeListLabel,LEFT))
		
		edgeListLabel.to_edge(LEFT)
		graph.scale(1.5)
		graph.to_edge(RIGHT)

		self.add(edgeListLabel,graph)

class Equation1(Scene):
	def construct(self):
		eq1 = MathTex("N_c","&=","C \\times C \\times C \\times \\cdots \\times C","\\\&=","C^{|V|}")
		eq1.scale(2)

		brace = Brace(eq1[2],direction=[0,1,0])
		label1 = Text("|V| times..")

		label1.next_to(brace,UP)

		self.add(eq1,brace,label1)

class Equation2(Scene):
	def construct(self):
		eq2 = MathTex("T","&=","1^{|V|} + 2^{|V|} + 3^{|V|} + \\cdots + \\chi ^{|V|} + \\cdots + |V|^{|V|}","\\\&=","\\sum_{n=1}^{n=|V|} n^{|V|}")

		self.add(eq2.scale(1.2))

class SolutionSpace(Scene):
	def construct(self):
		axes = Axes(x_range=[0,8,1],y_range=[0,5,1],tips=False)
		axLabels = axes.get_axis_labels(Tex('Indices').scale(0.7),Tex('Conflicts').scale(0.7))

		solutions = axes.plot(lambda x: 2.1-np.sin(x)-0.02*x*x*np.cos(5*x),color=BLUE)
		localMinimas = VGroup(Dot(axes.c2p(6.346,1.271)),Dot(axes.c2p(5.069,2.535)),Dot(axes.c2p(1.44,1.083)),Dot(axes.c2p(3.65,2.367)))
		globalMinima = Dot(axes.c2p(7.561,0.006),color=GREEN_C)
		
		dLabel1 = Dot(color=RED)
		label1 = VGroup(dLabel1,Text('Local Minima').next_to(dLabel1,RIGHT))

		dLabel2 = Dot(color=GREEN_C)
		label2 = VGroup(dLabel2,Text('Global Minima').next_to(dLabel2,RIGHT))

		label2.next_to(label1,DOWN)

		labels=VGroup(label1,label2)

		labels.to_corner(UR).scale(0.5)

		self.add(axes,axLabels,solutions,localMinimas.set_color(RED),globalMinima,labels)

--
-- PostgreSQL database dump
--

-- Dumped from database version 14.18 (Ubuntu 14.18-0ubuntu0.22.04.1)
-- Dumped by pg_dump version 14.18 (Ubuntu 14.18-0ubuntu0.22.04.1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: t_visualization; Type: TYPE; Schema: public; Owner: postgres
--

CREATE TYPE public.t_visualization AS ENUM (
    'before',
    'after',
    'none'
);


ALTER TYPE public.t_visualization OWNER TO postgres;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: units; Type: TABLE; Schema: public; Owner: slava
--

CREATE TABLE public.units (
    idunit integer NOT NULL,
    number integer NOT NULL,
    name text DEFAULT ''::text NOT NULL,
    parent integer DEFAULT '-1'::integer NOT NULL,
    type text DEFAULT ''::text NOT NULL,
    visualization public.t_visualization
);


ALTER TABLE public.units OWNER TO slava;

--
-- Name: units_idunit_seq; Type: SEQUENCE; Schema: public; Owner: slava
--

CREATE SEQUENCE public.units_idunit_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.units_idunit_seq OWNER TO slava;

--
-- Name: units_idunit_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: slava
--

ALTER SEQUENCE public.units_idunit_seq OWNED BY public.units.idunit;


--
-- Name: units idunit; Type: DEFAULT; Schema: public; Owner: slava
--

ALTER TABLE ONLY public.units ALTER COLUMN idunit SET DEFAULT nextval('public.units_idunit_seq'::regclass);


--
-- Data for Name: units; Type: TABLE DATA; Schema: public; Owner: slava
--

COPY public.units (idunit, number, name, parent, type, visualization) FROM stdin;
0	-1	ФСО	-1	ведомство	none
1	-1	Спецсвязь	0	служба	none
2	-1	СБП	0	служба	none
3	-1	УНТО	1	управление	none
4	-1	УЭССС	1	управление	none
5	-1	УШДС	1	управление	none
6	-1	секретариат	0	секретариат	none
7	-1	секретариат	1	секретариат	none
8	-1	секретариат	3	секретариат	none
9	-1	секретариат	4	секретариат	none
10	-1	секретариат	5	секретариат	none
11	-1	кадров	3	группа	before
12	-1	кадров	4	отделение	before
13	1		3	отдел	after
14	2		3	отдел	after
15	3		3	отдел	after
16	4		3	отдел	after
17	5		3	отдел	after
18	6		3	отдел	after
19	1		4	отдел	after
20	2		4	отдел	after
21	3		4	отдел	after
22	4		4	отдел	after
23	5		4	отдел	after
24	6		4	отдел	after
25	7		4	отдел	after
26	8		4	отдел	after
27	9		4	отдел	after
28	1		5	отдел	after
29	2		5	отдел	after
30	4		5	отдел	after
31	5		5	отдел	after
32	6		5	отдел	after
33	1		14	отделение	after
34	2		14	отделение	after
35	1		24	отделение	after
36	2		24	отделение	after
37	4		24	отделение	after
38	3		24	группа	after
39	1		27	отделение	after
40	2		27	отделение	after
\.


--
-- Name: units_idunit_seq; Type: SEQUENCE SET; Schema: public; Owner: slava
--

SELECT pg_catalog.setval('public.units_idunit_seq', 40, true);


--
-- PostgreSQL database dump complete
--

